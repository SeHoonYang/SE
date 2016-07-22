Public Class Form5

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim w As Integer = Integer.Parse(TextBox1.Text)
        Dim h As Integer = Integer.Parse(TextBox2.Text)
        Form1.map_x = w
        Form1.map_y = h
        For j = 0 To h - 1
            For i = 0 To w - 1
                If Form1.instantiated(w * j + i) = True Then

                Else
                    Form1.map_button(w * j + i) = New Button
                    Form1.instantiated(w * j + i) = True
                End If
                With Form1.map_button(w * j + i)
                    .Text = "□"
                    .FlatStyle = FlatStyle.Flat
                    .FlatAppearance.BorderSize = 0
                    .Size = New System.Drawing.Size(27, 27)
                    .Location = New System.Drawing.Point(3 + i * 27, 3 + 27 * j)
                    .Visible = True
                    .BackColor = Color.Black
                    .ForeColor = Color.White
                End With
                Form1.SplitContainer4.Panel1.Controls.Add(Form1.map_button(j * w + i))
                AddHandler Form1.map_button(j * w + i).MouseEnter, AddressOf Form1.MenuButtonHoverHandler
                AddHandler Form1.map_button(j * w + i).MouseClick, AddressOf Form1.MenuButtonClickHandler
            Next
        Next

        Dim index As Integer = 0
        Dim ts As String = ""

        TextBox3.Text = TextBox3.Text.Replace(vbCr, "").Replace(vbLf, "")
        TextBox4.Text = TextBox4.Text.Replace(vbCr, "").Replace(vbLf, "")

        For i = 0 To TextBox3.Text.Length - 1
            ts = ts + TextBox3.Text(i)
            If ts = "□" Or ts = "☆" Or ts = "★" Or ts = "○" Or ts = "●" Or ts = "◎" Or ts = "◇" Or ts = "◆" Or ts = "■" Or ts = "△" Or ts = "▲" Or ts = "▽" Or ts = "▼" Or ts = "◁" Or ts = "◀" Or ts = "▷" Or ts = "▶" Or ts = "◈" Or ts = "▣" Or ts = "─" Or ts = "│" Or ts = "┌" Or ts = "┐" Or ts = "┘" Or ts = "└" Or ts = "├" Or ts = "┬" Or ts = "┤" Or ts = "┴" Or ts = "┼" Or ts = "━" Or ts = "┃" Or ts = "┏" Or ts = "┓" Or ts = "┛" Or ts = "┗" Or ts = "┣" Or ts = "┫" Or ts = "┫" Or ts = "┻" Or ts = "╋" Or ts.Length = 2 Then
                Form1.map_button(index).Text = ts
                index = index + 1
                ts = ""
            End If
        Next

        If index <> w * h Then
            MsgBox("Import error;")
        End If

        index = 0
        ts = ""
        For i = 0 To TextBox4.Text.Length - 1
            ts = ts + TextBox4.Text(i)
            If ts.Length = 6 Then
                Dim ts2 = ts(0) + ts(1) + ts(2)
                Dim intcolor = Integer.Parse(ts2)
                Dim bgcolor As Integer = Math.Floor(intcolor / 16)
                Dim frcolor As Integer = intcolor Mod 16

                Select Case bgcolor
                    Case 0
                        Form1.map_button(index).BackColor = Color.Black
                    Case 1
                        Form1.map_button(index).BackColor = Color.Navy
                    Case 2
                        Form1.map_button(index).BackColor = Color.Green
                    Case 3
                        Form1.map_button(index).BackColor = Color.Teal
                    Case 4
                        Form1.map_button(index).BackColor = Color.Maroon
                    Case 5
                        Form1.map_button(index).BackColor = Color.Purple
                    Case 6
                        Form1.map_button(index).BackColor = Color.Olive
                    Case 7
                        Form1.map_button(index).BackColor = Form1.LightGrayToolStripMenuItem.ForeColor
                    Case 8
                        Form1.map_button(index).BackColor = Form1.DarkGrayToolStripMenuItem.ForeColor
                    Case 9
                        Form1.map_button(index).BackColor = Color.Blue
                    Case 10
                        Form1.map_button(index).BackColor = Color.Lime
                    Case 11
                        Form1.map_button(index).BackColor = Color.Cyan
                    Case 12
                        Form1.map_button(index).BackColor = Color.Red
                    Case 13
                        Form1.map_button(index).BackColor = Color.Magenta
                    Case 14
                        Form1.map_button(index).BackColor = Color.Yellow
                    Case 15
                        Form1.map_button(index).BackColor = Color.White
                End Select
                Select Case frcolor
                    Case 0
                        Form1.map_button(index).ForeColor = Color.Black
                    Case 1
                        Form1.map_button(index).ForeColor = Color.Navy
                    Case 2
                        Form1.map_button(index).ForeColor = Color.Green
                    Case 3
                        Form1.map_button(index).ForeColor = Color.Teal
                    Case 4
                        Form1.map_button(index).ForeColor = Color.Maroon
                    Case 5
                        Form1.map_button(index).ForeColor = Color.Purple
                    Case 6
                        Form1.map_button(index).ForeColor = Color.Olive
                    Case 7
                        Form1.map_button(index).ForeColor = Form1.LightGrayToolStripMenuItem.ForeColor
                    Case 8
                        Form1.map_button(index).ForeColor = Form1.DarkGrayToolStripMenuItem.ForeColor
                    Case 9
                        Form1.map_button(index).ForeColor = Color.Blue
                    Case 10
                        Form1.map_button(index).ForeColor = Color.Lime
                    Case 11
                        Form1.map_button(index).ForeColor = Color.Cyan
                    Case 12
                        Form1.map_button(index).ForeColor = Color.Red
                    Case 13
                        Form1.map_button(index).ForeColor = Color.Magenta
                    Case 14
                        Form1.map_button(index).ForeColor = Color.Yellow
                    Case 15
                        Form1.map_button(index).ForeColor = Color.White
                End Select
                ts = ""
                index = index + 1
            End If
        Next

        Me.Close()
    End Sub
End Class