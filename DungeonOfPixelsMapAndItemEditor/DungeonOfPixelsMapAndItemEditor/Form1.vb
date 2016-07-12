Public Class Form1

    Dim mode As Integer = -1
    Public menu_button(640) As Button
    Dim current_color As System.Drawing.Color = Color.Black
    Dim mouse_clicked As Boolean = False

    Private Sub MenuButtonHoverHandler(ByVal sender As Object, ByVal e As System.EventArgs)
        If mouse_clicked Then
            If mode = 1 Then
                CType(sender, Button).Text = ToolStripTextBox1.Text
            ElseIf mode = 2 Then
                CType(sender, Button).BackColor = current_color
            ElseIf mode = 3 Then
                CType(sender, Button).ForeColor = current_color
            ElseIf mode = 4 Then
                CType(sender, Button).Text = "  "
                CType(sender, Button).BackColor = Color.Black
                CType(sender, Button).ForeColor = Color.White
            End If
        End If
    End Sub
    Private Sub MenuButtonClickHandler(ByVal sender As Object, ByVal e As System.EventArgs)
            If mode = 1 Then
                CType(sender, Button).Text = ToolStripTextBox1.Text
            ElseIf mode = 2 Then
                CType(sender, Button).BackColor = current_color
            ElseIf mode = 3 Then
                CType(sender, Button).ForeColor = current_color
            ElseIf mode = 4 Then
                CType(sender, Button).Text = "  "
                CType(sender, Button).BackColor = Color.Black
                CType(sender, Button).ForeColor = Color.White
            End If
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        For i = 0 To 31
            For j = 0 To 19
                menu_button(j * 32 + i) = New Button
                With menu_button(j * 32 + i)
                    .Text = "□"
                    .FlatStyle = FlatStyle.Flat
                    .FlatAppearance.BorderSize = 0
                    .Size = New System.Drawing.Size(27, 27)
                    .Location = New System.Drawing.Point(3 + i * 27, 3 + j * 27)
                    .Visible = True
                    .BackColor = Color.Black
                    .ForeColor = Color.White
                End With
                TabPage3.Controls.Add(menu_button(j * 32 + i))
                AddHandler menu_button(j * 32 + i).MouseEnter, AddressOf MenuButtonHoverHandler
                AddHandler menu_button(j * 32 + i).MouseClick, AddressOf MenuButtonClickHandler
            Next
        Next
    End Sub

    Private Sub DrawText_Click(sender As Object, e As EventArgs) Handles DrawText.Click
        mode = 1
    End Sub

    Private Sub BackgroundColor_Click(sender As Object, e As EventArgs) Handles BackgroundColor.Click
        mode = 2
    End Sub

    Private Sub TextColor_Click(sender As Object, e As EventArgs) Handles TextColor.Click
        mode = 3
    End Sub

    Private Sub ToolStripButton1_Click(sender As Object, e As EventArgs) Handles ToolStripButton1.Click
        mode = 4
    End Sub

    Private Sub BlackToolStripMenuItem1_Click(sender As Object, e As EventArgs) Handles BlackToolStripMenuItem1.Click
        current_color = Color.Black
    End Sub

    Private Sub DarkGrayToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles DarkGrayToolStripMenuItem.Click
        current_color = DarkGrayToolStripMenuItem.ForeColor
    End Sub

    Private Sub LightGrayToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LightGrayToolStripMenuItem.Click
        current_color = LightGrayToolStripMenuItem.ForeColor
    End Sub

    Private Sub BlueToolStripMenuItem1_Click(sender As Object, e As EventArgs) Handles BlueToolStripMenuItem1.Click
        current_color = Color.Navy
    End Sub

    Private Sub LightBlueToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LightBlueToolStripMenuItem.Click
        current_color = Color.Blue
    End Sub

    Private Sub GreenToolStripMenuItem1_Click(sender As Object, e As EventArgs) Handles GreenToolStripMenuItem1.Click
        current_color = Color.Green
    End Sub

    Private Sub LightGreenToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LightGreenToolStripMenuItem.Click
        current_color = Color.Lime
    End Sub

    Private Sub GreenToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles GreenToolStripMenuItem.Click
        current_color = Color.Green
    End Sub

    Private Sub BlueToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles BlueToolStripMenuItem.Click
        current_color = Color.Navy
    End Sub

    Private Sub CyanToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CyanToolStripMenuItem.Click
        current_color = Color.Teal
    End Sub

    Private Sub CyanToolStripMenuItem1_Click(sender As Object, e As EventArgs) Handles CyanToolStripMenuItem1.Click
        current_color = Color.Teal
    End Sub

    Private Sub LightCyanToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LightCyanToolStripMenuItem.Click
        current_color = Color.Cyan
    End Sub

    Private Sub RedToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles RedToolStripMenuItem.Click
        current_color = Color.Maroon
    End Sub

    Private Sub RedToolStripMenuItem1_Click(sender As Object, e As EventArgs) Handles RedToolStripMenuItem1.Click
        current_color = Color.Maroon
    End Sub

    Private Sub LightRedToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LightRedToolStripMenuItem.Click
        current_color = Color.Red
    End Sub

    Private Sub MagentaToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles MagentaToolStripMenuItem.Click
        current_color = Color.Purple
    End Sub

    Private Sub MagentaToolStripMenuItem1_Click(sender As Object, e As EventArgs) Handles MagentaToolStripMenuItem1.Click
        current_color = Color.Purple
    End Sub

    Private Sub LightMagentaToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LightMagentaToolStripMenuItem.Click
        current_color = Color.Magenta
    End Sub

    Private Sub BrwonToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles BrwonToolStripMenuItem.Click
        current_color = Color.Olive
    End Sub

    Private Sub YellowToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles YellowToolStripMenuItem.Click
        current_color = Color.Yellow
    End Sub

    Private Sub WhiteToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles WhiteToolStripMenuItem.Click
        current_color = Color.White
    End Sub

    Private Sub Form1_KeyDown(sender As Object, e As KeyEventArgs) Handles MyBase.KeyDown
        mouse_clicked = True
    End Sub

    Private Sub Form1_KeyUp(sender As Object, e As KeyEventArgs) Handles MyBase.KeyUp
        mouse_clicked = False
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Dim GenText = ""
        For j = 0 To 19
            For i = 0 To 31
                If menu_button(j * 32 + i).Text = " " Then
                    GenText = GenText + "  "
                Else
                    GenText = GenText + menu_button(j * 32 + i).Text
                End If
            Next
        Next

        Dim GenColor = ""
        For j = 0 To 19
            For i = 0 To 31
                Dim c = 0
                Select Case menu_button(j * 32 + i).ForeColor
                    Case Color.Black
                        c = c + 0
                    Case Color.Navy
                        c = c + 1
                    Case Color.Green
                        c = c + 2
                    Case Color.Teal
                        c = c + 3
                    Case Color.Maroon
                        c = c + 4
                    Case Color.Purple
                        c = c + 5
                    Case Color.Olive
                        c = c + 6
                    Case LightGrayToolStripMenuItem.ForeColor
                        c = c + 7
                    Case DarkGrayToolStripMenuItem.ForeColor
                        c = c + 8
                    Case Color.Blue
                        c = c + 9
                    Case Color.Lime
                        c = c + 10
                    Case Color.Cyan
                        c = c + 11
                    Case Color.Red
                        c = c + 12
                    Case Color.Magenta
                        c = c + 13
                    Case Color.Yellow
                        c = c + 14
                    Case Color.White
                        c = c + 15
                End Select
                Select Case menu_button(j * 32 + i).BackColor
                    Case Color.Black
                        c = c + 0 * 16
                    Case Color.Navy
                        c = c + 1 * 16
                    Case Color.Green
                        c = c + 2 * 16
                    Case Color.Teal
                        c = c + 3 * 16
                    Case Color.Maroon
                        c = c + 4 * 16
                    Case Color.Purple
                        c = c + 5 * 16
                    Case Color.Olive
                        c = c + 6 * 16
                    Case LightGrayToolStripMenuItem.ForeColor
                        c = c + 7 * 16
                    Case DarkGrayToolStripMenuItem.ForeColor
                        c = c + 8 * 16
                    Case Color.Blue
                        c = c + 9 * 16
                    Case Color.Lime
                        c = c + 10 * 16
                    Case Color.Cyan
                        c = c + 11 * 16
                    Case Color.Red
                        c = c + 12 * 16
                    Case Color.Magenta
                        c = c + 13 * 16
                    Case Color.Yellow
                        c = c + 14 * 16
                    Case Color.White
                        c = c + 15 * 16
                End Select
                If c.ToString.Length = 1 Then
                    GenColor = GenColor + "00" + c.ToString + "00" + c.ToString
                ElseIf c.ToString.Length = 2 Then
                    GenColor = GenColor + "0" + c.ToString + "0" + c.ToString
                Else
                    GenColor = GenColor + c.ToString + c.ToString
                End If
            Next
        Next
        GenColor = GenColor
        Form2.TextBox1.Text = GenText
        Form2.TextBox2.Text = GenColor
        Form2.Show()
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        Form3.Show()
    End Sub

    Private Sub ToolStripButton2_Click(sender As Object, e As EventArgs) Handles ToolStripButton2.Click
        mode = 5
    End Sub

End Class
