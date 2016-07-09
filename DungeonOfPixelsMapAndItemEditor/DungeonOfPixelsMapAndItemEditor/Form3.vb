Public Class Form3

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim index As Integer = 0
        Dim ts As String = ""

        For i = 0 To TextBox1.Text.Length - 1
            ts = ts + TextBox1.Text(i)
            If ts = "□" Or ts = "☆" Or ts = "★" Or ts = "○" Or ts = "●" Or ts = "◎" Or ts = "◇" Or ts = "◆" Or ts = "■" Or ts = "△" Or ts = "▲" Or ts = "▽" Or ts = "▼" Or ts = "◁" Or ts = "◀" Or ts = "▷" Or ts = "▶" Or ts = "◈" Or ts = "▣" Or ts.Length = 2 Then
                Form1.menu_button(index).Text = ts
                index = index + 1
                ts = ""
            End If
        Next

        If index <> 640 Then
            MsgBox("Import error;")
        End If

        index = 0
        ts = ""
        For i = 0 To TextBox2.Text.Length - 1
            ts = ts + TextBox2.Text(i)
            If ts.Length = 6 Then
                Dim ts2 = ts(0) + ts(1) + ts(2)
                Dim intcolor = Integer.Parse(ts2)
                Dim bgcolor As Integer = Math.Floor(intcolor / 16)
                Dim frcolor As Integer = intcolor Mod 16

                Select Case bgcolor
                    Case 0
                        Form1.menu_button(index).BackColor = Color.Black
                    Case 1
                        Form1.menu_button(index).BackColor = Color.Navy
                    Case 2
                        Form1.menu_button(index).BackColor = Color.Green
                    Case 3
                        Form1.menu_button(index).BackColor = Color.Teal
                    Case 4
                        Form1.menu_button(index).BackColor = Color.Maroon
                    Case 5
                        Form1.menu_button(index).BackColor = Color.Purple
                    Case 6
                        Form1.menu_button(index).BackColor = Color.Olive
                    Case 7
                        Form1.menu_button(index).BackColor = Form1.LightGrayToolStripMenuItem.ForeColor
                    Case 8
                        Form1.menu_button(index).BackColor = Form1.DarkGrayToolStripMenuItem.ForeColor
                    Case 9
                        Form1.menu_button(index).BackColor = Color.Blue
                    Case 10
                        Form1.menu_button(index).BackColor = Color.Lime
                    Case 11
                        Form1.menu_button(index).BackColor = Color.Cyan
                    Case 12
                        Form1.menu_button(index).BackColor = Color.Red
                    Case 13
                        Form1.menu_button(index).BackColor = Color.Magenta
                    Case 14
                        Form1.menu_button(index).BackColor = Color.Yellow
                    Case 15
                        Form1.menu_button(index).BackColor = Color.White
                End Select
                Select Case frcolor
                    Case 0
                        Form1.menu_button(index).ForeColor = Color.Black
                    Case 1
                        Form1.menu_button(index).ForeColor = Color.Navy
                    Case 2
                        Form1.menu_button(index).ForeColor = Color.Green
                    Case 3
                        Form1.menu_button(index).ForeColor = Color.Teal
                    Case 4
                        Form1.menu_button(index).ForeColor = Color.Maroon
                    Case 5
                        Form1.menu_button(index).ForeColor = Color.Purple
                    Case 6
                        Form1.menu_button(index).ForeColor = Color.Olive
                    Case 7
                        Form1.menu_button(index).ForeColor = Form1.LightGrayToolStripMenuItem.ForeColor
                    Case 8
                        Form1.menu_button(index).ForeColor = Form1.DarkGrayToolStripMenuItem.ForeColor
                    Case 9
                        Form1.menu_button(index).ForeColor = Color.Blue
                    Case 10
                        Form1.menu_button(index).ForeColor = Color.Lime
                    Case 11
                        Form1.menu_button(index).ForeColor = Color.Cyan
                    Case 12
                        Form1.menu_button(index).ForeColor = Color.Red
                    Case 13
                        Form1.menu_button(index).ForeColor = Color.Magenta
                    Case 14
                        Form1.menu_button(index).ForeColor = Color.Yellow
                    Case 15
                        Form1.menu_button(index).ForeColor = Color.White
                End Select
                ts = ""
                index = index + 1
            End If
        Next

    End Sub
End Class