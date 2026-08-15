Option Explicit

Sub GenerateMermaidFlowchart()
    Dim wsInput As Worksheet
    Dim wsOutput As Worksheet
    Dim dictNodes As Object
    Dim dictShapeObj As Object


    On Error Resume Next
    Set wsInput = Worksheets("入力")
    Set wsOutput = Worksheets("出力")
    On Error GoTo 0

    If wsInput Is Nothing Or wsOutput Is Nothing Then
        MsgBox "「入力」シートまたは「出力」シートが見つかりません。", vbExclamation
        Exit Sub
    End If

    ' Dictionaryの初期化 (ノード情報の保持用)
    Set dictNodes = CreateObject("Scripting.Dictionary")
    Set dictShapeObj = CreateObject("Scripting.Dictionary")

    ' 出力シートの既存図形を削除
    wsOutput.Shapes.SelectAll
    Selection.Delete

    ' 1. 入力シートからMermaid構文の読み込みとノード/接続の抽出
    Dim rowIdx As Long
    Dim cellText As String
    Dim cellType As String
    Dim cellLabel As String
    Dim nodeConnections As Collection
    Dim shapeType As MsoAutoShapeType



    Set nodeConnections = New Collection
    rowIdx = 2
    Do
        cellLabel =  Trim(wsInput.Cells(rowIdx, 1).Value)
        cellType = Trim(wsInput.Cells(rowIdx, 2).Value)
        cellText = Trim(wsInput.Cells(rowIdx, 3).Value)

        If cellLabel = "" And cellType = "" And cellText = "" Then Exit Do
        If cellLabel = "" Then cellLabel = rowIdx.toString()

        ' 図形作成



        ' ----
        rowIdx = rowIdx + 1
    Loop

    MsgBox "終了", vbInformation

End Sub


' 括弧の種類からExcel図形（AutoShape）を選択
Private Function GetShapeType(ByVal rawStr As String) As MsoAutoShapeType
    Select Case rawStr.ToLower()
        Case "rectangle", "四角"
            Return MsoAutoShapeType.msoShapeRectangle
        Case "oval", "円"
            Return MsoAutoShapeType.msoShapeOval
        Case Else
            Return MsoAutoShapeType.msoShapeRectangle ' デフォルト値
    End Select
End Function
