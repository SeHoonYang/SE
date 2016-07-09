<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form은 Dispose를 재정의하여 구성 요소 목록을 정리합니다.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows Form 디자이너에 필요합니다.
    Private components As System.ComponentModel.IContainer

    '참고: 다음 프로시저는 Windows Form 디자이너에 필요합니다.
    '수정하려면 Windows Form 디자이너를 사용하십시오.  
    '코드 편집기를 사용하여 수정하지 마십시오.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.TabControl1 = New System.Windows.Forms.TabControl()
        Me.TabPage1 = New System.Windows.Forms.TabPage()
        Me.TabPage2 = New System.Windows.Forms.TabPage()
        Me.TabPage3 = New System.Windows.Forms.TabPage()
        Me.Button2 = New System.Windows.Forms.Button()
        Me.mother_cell = New System.Windows.Forms.Button()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.SplitContainer1 = New System.Windows.Forms.SplitContainer()
        Me.ToolStrip1 = New System.Windows.Forms.ToolStrip()
        Me.ToolStripTextBox1 = New System.Windows.Forms.ToolStripTextBox()
        Me.DrawText = New System.Windows.Forms.ToolStripButton()
        Me.ToolStripSplitButton1 = New System.Windows.Forms.ToolStripSplitButton()
        Me.BlackToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BlackToolStripMenuItem1 = New System.Windows.Forms.ToolStripMenuItem()
        Me.DarkGrayToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.LightGrayToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BlueToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BlueToolStripMenuItem1 = New System.Windows.Forms.ToolStripMenuItem()
        Me.LightBlueToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.GreenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.GreenToolStripMenuItem1 = New System.Windows.Forms.ToolStripMenuItem()
        Me.LightGreenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CyanToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CyanToolStripMenuItem1 = New System.Windows.Forms.ToolStripMenuItem()
        Me.LightCyanToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RedToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RedToolStripMenuItem1 = New System.Windows.Forms.ToolStripMenuItem()
        Me.LightRedToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.MagentaToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.MagentaToolStripMenuItem1 = New System.Windows.Forms.ToolStripMenuItem()
        Me.LightMagentaToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BrwonToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.YellowToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.WhiteToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.BackgroundColor = New System.Windows.Forms.ToolStripButton()
        Me.TextColor = New System.Windows.Forms.ToolStripButton()
        Me.ToolStripButton1 = New System.Windows.Forms.ToolStripButton()
        Me.TabControl1.SuspendLayout()
        Me.TabPage3.SuspendLayout()
        CType(Me.SplitContainer1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SplitContainer1.Panel1.SuspendLayout()
        Me.SplitContainer1.Panel2.SuspendLayout()
        Me.SplitContainer1.SuspendLayout()
        Me.ToolStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'TabControl1
        '
        Me.TabControl1.Controls.Add(Me.TabPage1)
        Me.TabControl1.Controls.Add(Me.TabPage2)
        Me.TabControl1.Controls.Add(Me.TabPage3)
        Me.TabControl1.Dock = System.Windows.Forms.DockStyle.Fill
        Me.TabControl1.Location = New System.Drawing.Point(0, 0)
        Me.TabControl1.Name = "TabControl1"
        Me.TabControl1.SelectedIndex = 0
        Me.TabControl1.Size = New System.Drawing.Size(846, 601)
        Me.TabControl1.TabIndex = 0
        '
        'TabPage1
        '
        Me.TabPage1.Location = New System.Drawing.Point(4, 22)
        Me.TabPage1.Name = "TabPage1"
        Me.TabPage1.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPage1.Size = New System.Drawing.Size(649, 455)
        Me.TabPage1.TabIndex = 0
        Me.TabPage1.Text = "Map Editor"
        Me.TabPage1.UseVisualStyleBackColor = True
        '
        'TabPage2
        '
        Me.TabPage2.Location = New System.Drawing.Point(4, 22)
        Me.TabPage2.Name = "TabPage2"
        Me.TabPage2.Padding = New System.Windows.Forms.Padding(3)
        Me.TabPage2.Size = New System.Drawing.Size(649, 455)
        Me.TabPage2.TabIndex = 1
        Me.TabPage2.Text = "Item Editor"
        Me.TabPage2.UseVisualStyleBackColor = True
        '
        'TabPage3
        '
        Me.TabPage3.Controls.Add(Me.Button2)
        Me.TabPage3.Controls.Add(Me.mother_cell)
        Me.TabPage3.Controls.Add(Me.Button1)
        Me.TabPage3.Location = New System.Drawing.Point(4, 22)
        Me.TabPage3.Name = "TabPage3"
        Me.TabPage3.Size = New System.Drawing.Size(838, 575)
        Me.TabPage3.TabIndex = 2
        Me.TabPage3.Text = "Menu Editor"
        Me.TabPage3.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Dock = System.Windows.Forms.DockStyle.Bottom
        Me.Button2.Location = New System.Drawing.Point(0, 529)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(838, 23)
        Me.Button2.TabIndex = 2
        Me.Button2.Text = "Import"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'mother_cell
        '
        Me.mother_cell.FlatAppearance.BorderSize = 0
        Me.mother_cell.FlatStyle = System.Windows.Forms.FlatStyle.Flat
        Me.mother_cell.Location = New System.Drawing.Point(3, 3)
        Me.mother_cell.Name = "mother_cell"
        Me.mother_cell.Size = New System.Drawing.Size(20, 20)
        Me.mother_cell.TabIndex = 1
        Me.mother_cell.UseVisualStyleBackColor = True
        Me.mother_cell.Visible = False
        '
        'Button1
        '
        Me.Button1.Dock = System.Windows.Forms.DockStyle.Bottom
        Me.Button1.Location = New System.Drawing.Point(0, 552)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(838, 23)
        Me.Button1.TabIndex = 0
        Me.Button1.Text = "GenerateMenu"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'SplitContainer1
        '
        Me.SplitContainer1.Dock = System.Windows.Forms.DockStyle.Fill
        Me.SplitContainer1.Location = New System.Drawing.Point(0, 0)
        Me.SplitContainer1.Name = "SplitContainer1"
        '
        'SplitContainer1.Panel1
        '
        Me.SplitContainer1.Panel1.Controls.Add(Me.TabControl1)
        '
        'SplitContainer1.Panel2
        '
        Me.SplitContainer1.Panel2.Controls.Add(Me.ToolStrip1)
        Me.SplitContainer1.Size = New System.Drawing.Size(894, 601)
        Me.SplitContainer1.SplitterDistance = 846
        Me.SplitContainer1.TabIndex = 3
        '
        'ToolStrip1
        '
        Me.ToolStrip1.Dock = System.Windows.Forms.DockStyle.Right
        Me.ToolStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ToolStripTextBox1, Me.DrawText, Me.ToolStripSplitButton1, Me.BackgroundColor, Me.TextColor, Me.ToolStripButton1})
        Me.ToolStrip1.Location = New System.Drawing.Point(11, 0)
        Me.ToolStrip1.Name = "ToolStrip1"
        Me.ToolStrip1.Size = New System.Drawing.Size(33, 601)
        Me.ToolStrip1.TabIndex = 3
        Me.ToolStrip1.Text = "ToolStrip1"
        '
        'ToolStripTextBox1
        '
        Me.ToolStripTextBox1.Name = "ToolStripTextBox1"
        Me.ToolStripTextBox1.Size = New System.Drawing.Size(28, 23)
        '
        'DrawText
        '
        Me.DrawText.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.DrawText.Image = CType(resources.GetObject("DrawText.Image"), System.Drawing.Image)
        Me.DrawText.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.DrawText.Name = "DrawText"
        Me.DrawText.Size = New System.Drawing.Size(30, 20)
        Me.DrawText.Text = "TextTool"
        '
        'ToolStripSplitButton1
        '
        Me.ToolStripSplitButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripSplitButton1.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.BlackToolStripMenuItem, Me.BlueToolStripMenuItem, Me.GreenToolStripMenuItem, Me.CyanToolStripMenuItem, Me.RedToolStripMenuItem, Me.MagentaToolStripMenuItem, Me.BrwonToolStripMenuItem, Me.YellowToolStripMenuItem, Me.WhiteToolStripMenuItem})
        Me.ToolStripSplitButton1.Image = CType(resources.GetObject("ToolStripSplitButton1.Image"), System.Drawing.Image)
        Me.ToolStripSplitButton1.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripSplitButton1.Name = "ToolStripSplitButton1"
        Me.ToolStripSplitButton1.Size = New System.Drawing.Size(30, 20)
        Me.ToolStripSplitButton1.Text = "4"
        '
        'BlackToolStripMenuItem
        '
        Me.BlackToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.BlackToolStripMenuItem1, Me.DarkGrayToolStripMenuItem, Me.LightGrayToolStripMenuItem})
        Me.BlackToolStripMenuItem.Name = "BlackToolStripMenuItem"
        Me.BlackToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.BlackToolStripMenuItem.Text = "Black"
        '
        'BlackToolStripMenuItem1
        '
        Me.BlackToolStripMenuItem1.Name = "BlackToolStripMenuItem1"
        Me.BlackToolStripMenuItem1.Size = New System.Drawing.Size(125, 22)
        Me.BlackToolStripMenuItem1.Text = "Black"
        '
        'DarkGrayToolStripMenuItem
        '
        Me.DarkGrayToolStripMenuItem.ForeColor = System.Drawing.SystemColors.GrayText
        Me.DarkGrayToolStripMenuItem.Name = "DarkGrayToolStripMenuItem"
        Me.DarkGrayToolStripMenuItem.Size = New System.Drawing.Size(125, 22)
        Me.DarkGrayToolStripMenuItem.Text = "DarkGray"
        '
        'LightGrayToolStripMenuItem
        '
        Me.LightGrayToolStripMenuItem.ForeColor = System.Drawing.Color.Silver
        Me.LightGrayToolStripMenuItem.Name = "LightGrayToolStripMenuItem"
        Me.LightGrayToolStripMenuItem.Size = New System.Drawing.Size(125, 22)
        Me.LightGrayToolStripMenuItem.Text = "LightGray"
        '
        'BlueToolStripMenuItem
        '
        Me.BlueToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.BlueToolStripMenuItem1, Me.LightBlueToolStripMenuItem})
        Me.BlueToolStripMenuItem.ForeColor = System.Drawing.Color.Navy
        Me.BlueToolStripMenuItem.Name = "BlueToolStripMenuItem"
        Me.BlueToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.BlueToolStripMenuItem.Text = "Blue"
        '
        'BlueToolStripMenuItem1
        '
        Me.BlueToolStripMenuItem1.ForeColor = System.Drawing.Color.Navy
        Me.BlueToolStripMenuItem1.Name = "BlueToolStripMenuItem1"
        Me.BlueToolStripMenuItem1.Size = New System.Drawing.Size(124, 22)
        Me.BlueToolStripMenuItem1.Text = "Blue"
        '
        'LightBlueToolStripMenuItem
        '
        Me.LightBlueToolStripMenuItem.ForeColor = System.Drawing.Color.Blue
        Me.LightBlueToolStripMenuItem.Name = "LightBlueToolStripMenuItem"
        Me.LightBlueToolStripMenuItem.Size = New System.Drawing.Size(124, 22)
        Me.LightBlueToolStripMenuItem.Text = "LightBlue"
        '
        'GreenToolStripMenuItem
        '
        Me.GreenToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.GreenToolStripMenuItem1, Me.LightGreenToolStripMenuItem})
        Me.GreenToolStripMenuItem.ForeColor = System.Drawing.Color.Green
        Me.GreenToolStripMenuItem.Name = "GreenToolStripMenuItem"
        Me.GreenToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.GreenToolStripMenuItem.Text = "Green"
        '
        'GreenToolStripMenuItem1
        '
        Me.GreenToolStripMenuItem1.ForeColor = System.Drawing.Color.Green
        Me.GreenToolStripMenuItem1.Name = "GreenToolStripMenuItem1"
        Me.GreenToolStripMenuItem1.Size = New System.Drawing.Size(132, 22)
        Me.GreenToolStripMenuItem1.Text = "Green"
        '
        'LightGreenToolStripMenuItem
        '
        Me.LightGreenToolStripMenuItem.ForeColor = System.Drawing.Color.Lime
        Me.LightGreenToolStripMenuItem.Name = "LightGreenToolStripMenuItem"
        Me.LightGreenToolStripMenuItem.Size = New System.Drawing.Size(132, 22)
        Me.LightGreenToolStripMenuItem.Text = "LightGreen"
        '
        'CyanToolStripMenuItem
        '
        Me.CyanToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.CyanToolStripMenuItem1, Me.LightCyanToolStripMenuItem})
        Me.CyanToolStripMenuItem.ForeColor = System.Drawing.Color.Teal
        Me.CyanToolStripMenuItem.Name = "CyanToolStripMenuItem"
        Me.CyanToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.CyanToolStripMenuItem.Text = "Cyan"
        '
        'CyanToolStripMenuItem1
        '
        Me.CyanToolStripMenuItem1.ForeColor = System.Drawing.Color.Teal
        Me.CyanToolStripMenuItem1.Name = "CyanToolStripMenuItem1"
        Me.CyanToolStripMenuItem1.Size = New System.Drawing.Size(128, 22)
        Me.CyanToolStripMenuItem1.Text = "Cyan"
        '
        'LightCyanToolStripMenuItem
        '
        Me.LightCyanToolStripMenuItem.ForeColor = System.Drawing.Color.Cyan
        Me.LightCyanToolStripMenuItem.Name = "LightCyanToolStripMenuItem"
        Me.LightCyanToolStripMenuItem.Size = New System.Drawing.Size(128, 22)
        Me.LightCyanToolStripMenuItem.Text = "LightCyan"
        '
        'RedToolStripMenuItem
        '
        Me.RedToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.RedToolStripMenuItem1, Me.LightRedToolStripMenuItem})
        Me.RedToolStripMenuItem.ForeColor = System.Drawing.Color.Maroon
        Me.RedToolStripMenuItem.Name = "RedToolStripMenuItem"
        Me.RedToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.RedToolStripMenuItem.Text = "Red"
        '
        'RedToolStripMenuItem1
        '
        Me.RedToolStripMenuItem1.ForeColor = System.Drawing.Color.Maroon
        Me.RedToolStripMenuItem1.Name = "RedToolStripMenuItem1"
        Me.RedToolStripMenuItem1.Size = New System.Drawing.Size(121, 22)
        Me.RedToolStripMenuItem1.Text = "Red"
        '
        'LightRedToolStripMenuItem
        '
        Me.LightRedToolStripMenuItem.ForeColor = System.Drawing.Color.Red
        Me.LightRedToolStripMenuItem.Name = "LightRedToolStripMenuItem"
        Me.LightRedToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.LightRedToolStripMenuItem.Text = "LightRed"
        '
        'MagentaToolStripMenuItem
        '
        Me.MagentaToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.MagentaToolStripMenuItem1, Me.LightMagentaToolStripMenuItem})
        Me.MagentaToolStripMenuItem.ForeColor = System.Drawing.Color.Purple
        Me.MagentaToolStripMenuItem.Name = "MagentaToolStripMenuItem"
        Me.MagentaToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.MagentaToolStripMenuItem.Text = "Magenta"
        '
        'MagentaToolStripMenuItem1
        '
        Me.MagentaToolStripMenuItem1.ForeColor = System.Drawing.Color.Purple
        Me.MagentaToolStripMenuItem1.Name = "MagentaToolStripMenuItem1"
        Me.MagentaToolStripMenuItem1.Size = New System.Drawing.Size(148, 22)
        Me.MagentaToolStripMenuItem1.Text = "Magenta"
        '
        'LightMagentaToolStripMenuItem
        '
        Me.LightMagentaToolStripMenuItem.ForeColor = System.Drawing.Color.Magenta
        Me.LightMagentaToolStripMenuItem.Name = "LightMagentaToolStripMenuItem"
        Me.LightMagentaToolStripMenuItem.Size = New System.Drawing.Size(148, 22)
        Me.LightMagentaToolStripMenuItem.Text = "LightMagenta"
        '
        'BrwonToolStripMenuItem
        '
        Me.BrwonToolStripMenuItem.ForeColor = System.Drawing.Color.Olive
        Me.BrwonToolStripMenuItem.Name = "BrwonToolStripMenuItem"
        Me.BrwonToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.BrwonToolStripMenuItem.Text = "Brown"
        '
        'YellowToolStripMenuItem
        '
        Me.YellowToolStripMenuItem.ForeColor = System.Drawing.Color.Yellow
        Me.YellowToolStripMenuItem.Name = "YellowToolStripMenuItem"
        Me.YellowToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.YellowToolStripMenuItem.Text = "Yellow"
        '
        'WhiteToolStripMenuItem
        '
        Me.WhiteToolStripMenuItem.ForeColor = System.Drawing.Color.Black
        Me.WhiteToolStripMenuItem.Name = "WhiteToolStripMenuItem"
        Me.WhiteToolStripMenuItem.Size = New System.Drawing.Size(121, 22)
        Me.WhiteToolStripMenuItem.Text = "White"
        '
        'BackgroundColor
        '
        Me.BackgroundColor.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.BackgroundColor.Image = CType(resources.GetObject("BackgroundColor.Image"), System.Drawing.Image)
        Me.BackgroundColor.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.BackgroundColor.Name = "BackgroundColor"
        Me.BackgroundColor.Size = New System.Drawing.Size(30, 20)
        Me.BackgroundColor.Text = "BackgroundColorTool"
        '
        'TextColor
        '
        Me.TextColor.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.TextColor.Image = CType(resources.GetObject("TextColor.Image"), System.Drawing.Image)
        Me.TextColor.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.TextColor.Name = "TextColor"
        Me.TextColor.Size = New System.Drawing.Size(30, 20)
        Me.TextColor.Text = "ForeColorTool"
        '
        'ToolStripButton1
        '
        Me.ToolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ToolStripButton1.Image = CType(resources.GetObject("ToolStripButton1.Image"), System.Drawing.Image)
        Me.ToolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ToolStripButton1.Name = "ToolStripButton1"
        Me.ToolStripButton1.Size = New System.Drawing.Size(30, 20)
        Me.ToolStripButton1.Text = "Eraser"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(7.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(894, 601)
        Me.Controls.Add(Me.SplitContainer1)
        Me.KeyPreview = True
        Me.Name = "Form1"
        Me.Text = "Editor"
        Me.TabControl1.ResumeLayout(False)
        Me.TabPage3.ResumeLayout(False)
        Me.SplitContainer1.Panel1.ResumeLayout(False)
        Me.SplitContainer1.Panel2.ResumeLayout(False)
        Me.SplitContainer1.Panel2.PerformLayout()
        CType(Me.SplitContainer1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.SplitContainer1.ResumeLayout(False)
        Me.ToolStrip1.ResumeLayout(False)
        Me.ToolStrip1.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents TabControl1 As System.Windows.Forms.TabControl
    Friend WithEvents TabPage1 As System.Windows.Forms.TabPage
    Friend WithEvents TabPage2 As System.Windows.Forms.TabPage
    Friend WithEvents TabPage3 As System.Windows.Forms.TabPage
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents SplitContainer1 As System.Windows.Forms.SplitContainer
    Friend WithEvents ToolStrip1 As System.Windows.Forms.ToolStrip
    Friend WithEvents DrawText As System.Windows.Forms.ToolStripButton
    Friend WithEvents BackgroundColor As System.Windows.Forms.ToolStripButton
    Friend WithEvents TextColor As System.Windows.Forms.ToolStripButton
    Friend WithEvents mother_cell As System.Windows.Forms.Button
    Friend WithEvents ToolStripTextBox1 As System.Windows.Forms.ToolStripTextBox
    Friend WithEvents ToolStripSplitButton1 As System.Windows.Forms.ToolStripSplitButton
    Friend WithEvents BlackToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents BlueToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents GreenToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CyanToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RedToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents MagentaToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents BrwonToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents BlueToolStripMenuItem1 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents LightBlueToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents GreenToolStripMenuItem1 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents LightGreenToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CyanToolStripMenuItem1 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents LightCyanToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RedToolStripMenuItem1 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents LightRedToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents MagentaToolStripMenuItem1 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents LightMagentaToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents YellowToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents WhiteToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents BlackToolStripMenuItem1 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents DarkGrayToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents LightGrayToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ToolStripButton1 As System.Windows.Forms.ToolStripButton
    Friend WithEvents Button2 As System.Windows.Forms.Button

End Class
