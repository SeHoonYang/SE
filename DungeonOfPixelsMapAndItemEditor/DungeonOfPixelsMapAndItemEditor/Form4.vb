Public Class Form4

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim w As Integer = Integer.Parse(TextBox1.Text)
        Dim h As Integer = Integer.Parse(TextBox2.Text)
        Form1.map_x = w
        Form1.map_y = h
        For i = 0 To w - 1
            For j = 0 To h - 1
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

        Me.Close()
    End Sub
End Class