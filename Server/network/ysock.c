#include <stdio.h>
#include "ysock.h"
#include "packet.h"
#include "../usr/usr.h"
#include "../lib/lib.h"
#include "../game/map_data.h"

static int buffer_size;
static int user_index;
static int total_thread;
static int closed;

void stop_data_loop()
{
  closed = 1;
}

void data_rs_loop(SOCKET c)
{
  char buffer[sizeof(struct packet) + 1];
  int error_count = 0;
  int sent_user = -1;

  while(!closed)
  {
    /* Receive a packet.
       Note that we will use large buffer to
       receive the data in a single loop     */
    int recv_amount = recv(c, buffer, buffer_size, 0);

    if(recv_amount < 0)
      error_count++;
    else
      error_count = 0;

    /* Connection lost */
    if(error_count > 20)
    {
      printf("Connection has been lost : %s\n", get_user_data(sent_user)->id);
      save_user_data(sent_user);
      release_user_data(sent_user);
      close_socket(c);
      total_thread--;
      return;
    }

    /* Analyze the packet */
    int invalid = !pkt_isvalid((struct packet *)buffer);
    int pkt_header = ((struct packet *)buffer)->header;
    int create_new_thread = 0;

    /* Create a packet */
    struct packet* to_send;
    
    if(invalid)
    {
      to_send = init_packet(0);
    }
    else
    {
      if(pkt_header == 1)
        to_send = init_packet(2);
      else if(pkt_header == 6)
        to_send = init_packet(7);
      else if(pkt_header == 3)
        to_send = init_packet(4);
      else if(pkt_header == 9)
        to_send = init_packet(10);
    }

    /* Server operation */
    if(!invalid)
    {
      if(pkt_header == 3)
      {
        /* Update server state and give result to the client */
        char key = ((struct packet *)buffer)->buffer[0];
        sent_user = *(int *)(((struct packet *)buffer)->buffer+1);

        struct enemy_info* info = NULL;
        /* Arrow keys */
        if(key == 72 || key == 75 || key == 77 || key == 80)
          info = update_user_location(sent_user, key);
        else if(key == 0)
        {
          /* Do nothing */
        }
        else
        {
          /* Not implemented yet */
        }

        /* Get server state */
        char server_data_buffer[BUFFER_SIZE-2];
        get_map_status(get_user_map_id(sent_user), server_data_buffer);
        marshal_packet(to_send, server_data_buffer, BUFFER_SIZE-2, 0);

        /* Page fault with info; have to be fixed */
        if(info != NULL && info->current_mob_id != -1)
        {
          marshal_packet(to_send, (char *)&(info->current_mob_id), 4, BUFFER_SIZE-6);
          marshal_packet(to_send, (char *)&(info->current_mob_hp), 2, BUFFER_SIZE-2);
          to_send->header = 5;
        }

        if(info != NULL)
          free(info);

      }
      else if(pkt_header == 9)
      {
        /* General menu request */
        struct user_data* d = get_user_data(sent_user);

        marshal_packet(to_send, (char *)&d->hp, 2, 0);
        marshal_packet(to_send, (char *)&d->max_hp, 2, 2);
        marshal_packet(to_send, (char *)&d->mp, 2, 4);
        marshal_packet(to_send, (char *)&d->max_mp, 2, 6);
        marshal_packet(to_send, (char *)&d->str, 2, 8);
        marshal_packet(to_send, (char *)&d->def, 2, 10);
        marshal_packet(to_send, (char *)&d->money, 4, 12);
        marshal_packet(to_send, (char *)&d->level, 2, 16);
        marshal_packet(to_send, (char *)&d->exp, 4, 18);
        marshal_packet(to_send, (char *)&d->stat_point, 2, 22);
      }
    }

    /* Send state of the server */
    send(c, (char *)to_send, sizeof(struct packet), 0);

    /* Free the packet */
    free_packet(to_send);
  }

  close(c);
}

int init_socket(int s)
{
  buffer_size = s;
  WSADATA wsa;
  return WSAStartup(MAKEWORD(2,2), &wsa);
}

int init_server(SOCKET* s, int port)
{
  struct sockaddr_in server;

  if((*s = socket(PF_INET, SOCK_STREAM,0)) == INVALID_SOCKET)
    return WSAGetLastError();

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(port);

  if(bind(*s, (struct sockaddr *)&server, sizeof(struct sockaddr)) == SOCKET_ERROR)
    return WSAGetLastError();

  closed = 0;

  return 0;
}

int connect_client(SOCKET* s, int port, char* host)
{
  struct sockaddr_in client;

  if((*s = socket(PF_INET, SOCK_STREAM,0)) == INVALID_SOCKET)
    return WSAGetLastError();

  client.sin_addr.s_addr = inet_addr(host);
  client.sin_family = AF_INET;
  client.sin_port = htons(port);

  connect(*s, (struct sockaddr *)&client, sizeof(client));

  return 0;
}

void open_server(SOCKET s, int queue)
{
  listen(s, queue);
}

void start_server(SOCKET s)
{
  SOCKET client;
  struct sockaddr_in client_addr;
  char buffer[sizeof(struct packet) + 1];
  int c = sizeof(struct sockaddr_in);

  while(1)
  {
    client = accept(s, (struct sockaddr *)&client_addr, &c);

    /* Receive a packet.
       Note that we will use large buffer to
       receive the data in a single loop     */
    recv(client, buffer, buffer_size, 0);

    /* Analyze the packet */
    int invalid = !pkt_isvalid((struct packet *)buffer);
    int pkt_header = ((struct packet *)buffer)->header;
    int create_new_thread = 0;

    /* Create a packet */
    struct packet* to_send = (struct packet *)NULL;
    
    if(invalid)
    {
      to_send = init_packet(0);
    }
    else
    {
      if(pkt_header == 1)
        to_send = init_packet(2);
      else if(pkt_header == 6)
        to_send = init_packet(7);
      else if(pkt_header == 3)
        to_send = init_packet(4);
      else if(pkt_header == 8)
        to_send = init_packet(0);
      else
        to_send = (struct packet *)NULL;
    }

    /* Server operation */
    if(!invalid)
    {
      if(pkt_header == 1)
      {
        /* Account creation request */

        int success = create_account(((struct packet *)buffer)->buffer, ((struct packet *)buffer)->buffer+11);
        printf("Account creation request : %s (%s)\n", ((struct packet *)buffer)->buffer, success == 1 ? "Success" : "Fail");

        char data_buffer[1];
        data_buffer[0] = success + '0';
        marshal_packet(to_send, data_buffer, 1, 0);
      }
      else if(pkt_header == 6)
      {
        /* Log in request */

        char id[11], pwd[11], buf[23];

        /* Resolve the packet data */
        memcpy(id, ((struct packet *)buffer)->buffer, 11);
        memcpy(pwd, ((struct packet *)buffer)->buffer+11, 11);

        /* Change current directory */
        chdir("./data/userdata/");

        /* Compare passwords */
        int success = 1;
        FILE* user_file = fopen(id,"r");

        if(user_file == NULL)
          success = 0;
        else
        {
          fgets(buf,12,user_file);
          buf[strlen(buf)-1] = 0;
          success = !strcmp(buf,pwd);
        }

        printf("Log in request : %s (%s)\n", ((struct packet *)buffer)->buffer, success == 1 ? "Success" : "Fail");

        if(success)
        {
          /* Load user data to the map data cache */
          int mid, money, exp;
          unsigned short x,y,hp,mp, max_hp, max_mp, str, def, level, stat_point;
          unsigned pos, h, m;
          char* token;

          fgets(buf,12,user_file);
          buf[strlen(buf)-1] = 0;
          mid = strn_to_int(buf, 12);

          fgets(buf,12,user_file);
          token = strtok(buf," ");
          x = (unsigned short)strn_to_int(token,5);
          token = strtok(NULL," ");
          token[strlen(token)-1] = 0;
          y = (unsigned short)strn_to_int(token,5);
          pos = 65536 * y + x;

          fgets(buf,12,user_file);
          token = strtok(buf," ");
          hp = (unsigned short)strn_to_int(token,5);
          token = strtok(NULL," ");
          token[strlen(token)-1] = 0;
          mp = (unsigned short)strn_to_int(token,5);
          h = 65536 * mp + hp;

          fgets(buf,12,user_file);
          token = strtok(buf," ");
          max_hp = (unsigned short)strn_to_int(token,5);
          token = strtok(NULL," ");
          token[strlen(token)-1] = 0;
          max_mp = (unsigned short)strn_to_int(token,5);
          m = 65536 * max_mp + max_hp;

          fgets(buf,12,user_file);
          token = strtok(buf," ");
          token[strlen(token)-1] = 0;
          money = strn_to_int(token,20);

          fgets(buf,23,user_file);
          token = strtok(buf," ");
          str = (unsigned short)strn_to_int(token,5);
          token = strtok(NULL," ");
          def = (unsigned short)strn_to_int(token,5);
          token = strtok(NULL," ");
          stat_point = (unsigned short)strn_to_int(token,5);
          token[strlen(token)-1] = 0;

          fgets(buf,23,user_file);
          token = strtok(buf," ");
          level = (unsigned short)strn_to_int(token,5);
          token = strtok(NULL," ");
          token[strlen(token)-1] = 0;
          exp = strn_to_int(token,12);

          /* Load user data to the cache. Not yet overlapped login handled */
          if(load_user_data(id, pwd, user_index, mid, pos, h, m, money, str, def, level, exp, stat_point) == 0)
            add_user_to_map(mid, user_index);
          else
            success = 0;

          /* Cache must be implemented with hash, but temporarily implemented with linked list */
          fclose(user_file);
        }

        char data_buffer[1];
        data_buffer[0] = success + '0';
        marshal_packet(to_send, data_buffer, 1, 0);
        marshal_packet(to_send, (char *)&user_index, 4, 1);

        /* Increase user index */
        if(success)
          user_index++;

        /* Return to the base directory */
        chdir("../../");
      }
      else if(pkt_header == 8)
      {
        /* Create new thread */
        create_new_thread = 1;
        printf("New thread has been created, total %d + 2 threads(inaccurate)\n", ++total_thread);
      }
    }

    /* Send state of the server */
    send(client, (char *)to_send, sizeof(struct packet), 0);

    /* Free the packet */
    if(to_send != NULL)
      free_packet(to_send);

    if(create_new_thread)
      _beginthread(data_rs_loop, 0, client);
    else
      close(client);
  }
}

void close_socket(SOCKET s)
{
  closesocket(s);
}

void end_socket()
{
  WSACleanup();
}