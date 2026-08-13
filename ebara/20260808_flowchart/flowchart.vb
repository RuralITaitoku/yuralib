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
    Dim lineText As String
    Dim nodeConnections As Collection
    Set nodeConnections = New Collection

    rowIdx = 1
    Do
        lineText = Trim(wsInput.Cells(rowIdx, 1).Value)
        If lineText = "" Then Exit Do

        ' コメント行・指向指定行(graph TD等)をスキップ
        If Left(lineText, 2) <> "%%" And Not lineText Like "graph *" And Not lineText Like "flowchart *" Then
            Call ParseMermaidLine(lineText, dictNodes, nodeConnections)
        End If

        rowIdx = rowIdx + 1
    Loop

    If dictNodes.Count = 0 Then
        MsgBox "有効なフローチャート定義が見つかりませんでした。", vbInformation
        Exit Sub
    End If

    ' 2. ノードのレイアウト配置と図形描画
    Dim nodeKey As Variant
    Dim topOffset As Double, leftOffset As Double
    Dim nodeWidth As Double, nodeHeight As Double
    Dim nodeSpacingY As Double, nodeSpacingX As Double

    nodeWidth = 120
    nodeHeight = 50
    nodeSpacingY = 40
    nodeSpacingX = 50
    leftOffset = 50
    topOffset = 50

    ' ノードの配置インデックス計算 (簡易階層レイアウト)
    Dim nodeLevel As Object
    Set nodeLevel = CalculateNodeLevels(dictNodes, nodeConnections)

    ' レベルごとのノードカウント
    Dim levelCounts As Object
    Set levelCounts = CreateObject("Scripting.Dictionary")

    Dim nodeID As String, labelText As String, shapeType As MsoAutoShapeType
    Dim lvl As Long, posX As Double, posY As Double
    Dim shp As Shape

    For Each nodeKey In dictNodes.Keys
        nodeID = CStr(nodeKey)
        labelText = dictNodes(nodeID)
        lvl = nodeLevel(nodeID)

        If Not levelCounts.Exists(lvl) Then levelCounts(lvl) = 0

        ' 配置位置の計算
        posX = leftOffset + (lvl * (nodeWidth + nodeSpacingX))
        posY = topOffset + (levelCounts(lvl) * (nodeHeight + nodeSpacingY))
        levelCounts(lvl) = levelCounts(lvl) + 1

        ' 図形種別の判定（テキスト内の括弧の種類で判定）
        shapeType = GetShapeType(labelText)

        ' 括弧を取り除いたラベル文字の抽出
        Dim cleanLabel As String
        cleanLabel = CleanNodeLabel(labelText)

        ' 図形の作成
        Set shp = wsOutput.Shapes.AddShape(shapeType, posX, posY, nodeWidth, nodeHeight)
        With shp
            .TextFrame2.TextRange.Text = cleanLabel
            .TextFrame2.TextRange.Font.Size = 10
            .TextFrame2.TextRange.Font.Fill.ForeColor.RGB = RGB(0, 0, 0)
            .TextFrame2.VerticalAnchor = msoAnchorMiddle
            .TextFrame2.TextRange.ParagraphFormat.Alignment = msoAlignCenter
            .Fill.ForeColor.RGB = RGB(235, 243, 250)
            .line.ForeColor.RGB = RGB(70, 130, 180)
            .line.Weight = 1.5
        End With

        Set dictShapeObj(nodeID) = shp
    Next nodeKey

    ' 3. コネクタ（矢印）の接続
    Dim conn As Variant
    Dim fromID As String, toID As String, connLabel As String
    Dim connShp As Shape

    For Each conn In nodeConnections
        fromID = conn("from")
        toID = conn("to")
        connLabel = conn("label")

        If dictShapeObj.Exists(fromID) And dictShapeObj.Exists(toID) Then
            Set connShp = wsOutput.Shapes.AddConnector(msoConnectorStraight, 0, 0, 100, 100)
            With connShp
                .ConnectorFormat.BeginConnect dictShapeObj(fromID), 4 ' 右側アンカー
                .ConnectorFormat.EndConnect dictShapeObj(toID), 2   ' 左側アンカー
                .line.EndArrowheadStyle = msoArrowheadTriangle
                .line.ForeColor.RGB = RGB(100, 100, 100)
                .line.Weight = 1.2
            End With
        End If
    Next conn

    wsOutput.Activate
    MsgBox "フローチャートの生成が完了しました！", vbInformation
End Sub

' --- 行構文の解析ルーチン ---
Private Sub ParseMermaidLine(ByVal line As String, ByRef dictNodes As Object, ByRef nodeConnections As Collection)
    ' 矢印記号（-->）が含まれる接続行の処理
    If InStr(line, "-->") > 0 Then
        Dim parts() As String
        parts = Split(line, "-->")

        Dim leftPart As String, rightPart As String
        leftPart = Trim(parts(0))
        rightPart = Trim(parts(1))

        Dim fromID As String, toID As String
        Dim connLabel As String

        fromID = ExtractNodeID(leftPart)
        Call RegisterNode(leftPart, dictNodes)

        ' パイプ記号による矢印ラベルの判定 (例: A -->|Yes| B)
        If Left(rightPart, 1) = "|" Then
            Dim pipeEnd As Long
            pipeEnd = InStr(2, rightPart, "|")
            If pipeEnd > 0 Then
                connLabel = Mid(rightPart, 2, pipeEnd - 2)
                rightPart = Trim(Mid(rightPart, pipeEnd + 1))
            End If
        End If

        toID = ExtractNodeID(rightPart)
        Call RegisterNode(rightPart, dictNodes)

        ' 接続情報の追加
        Dim connInfo As Object
        Set connInfo = CreateObject("Scripting.Dictionary")
        connInfo("from") = fromID
        connInfo("to") = toID
        connInfo("label") = connLabel
        nodeConnections.Add connInfo
    Else
        ' ノード単体定義の処理
        If line <> "" Then Call RegisterNode(line, dictNodes)
    End If
End Sub

Private Sub RegisterNode(ByVal rawStr As String, ByRef dictNodes As Object)
    Dim id As String
    id = ExtractNodeID(rawStr)
    If id = "" Then Exit Sub

    If Not dictNodes.Exists(id) Then
        dictNodes(id) = rawStr
    ElseIf InStr(rawStr, "[") > 0 Or InStr(rawStr, "(") > 0 Or InStr(rawStr, "{") > 0 Then
        ' より詳細な定義（ラベル付き）で更新
        dictNodes(id) = rawStr
    End If
End Sub

Private Function ExtractNodeID(ByVal rawStr As String) As String
    Dim p As Long
    p = InStr(rawStr, "[")
    If p = 0 Then p = InStr(rawStr, "(")
    If p = 0 Then p = InStr(rawStr, "{")

    If p > 0 Then
        ExtractNodeID = Trim(Left(rawStr, p - 1))
    Else
        ExtractNodeID = Trim(rawStr)
    End If
End Function

Private Function CleanNodeLabel(ByVal rawStr As String) As String
    Dim id As String, label As String
    id = ExtractNodeID(rawStr)

    Dim pStart As Long, pEnd As Long
    pStart = InStr(rawStr, "[")
    If pStart = 0 Then pStart = InStr(rawStr, "(")
    If pStart = 0 Then pStart = InStr(rawStr, "{")

    If pStart > 0 Then
        label = Mid(rawStr, pStart + 1)
        label = Left(label, Len(label) - 1)
        ' 丸括弧/ひし形の2重閉じを整形
        label = Replace(label, ")", "")
        label = Replace(label, "}", "")
        label = Replace(label, "]", "")
        CleanNodeLabel = Trim(label)
    Else
        CleanNodeLabel = id
    End If
End Function

' 括弧の種類からExcel図形（AutoShape）を選択
Private Function GetShapeType(ByVal rawStr As String) As MsoAutoShapeType
    If InStr(rawStr, "{") > 0 Then
        GetShapeType = msoShapeDiamond              ' ひし形（分岐）
    ElseIf InStr(rawStr, "((") > 0 Then
        GetShapeType = msoShapeOval                 ' 丸（開始/終了）
    ElseIf InStr(rawStr, "([") > 0 Then
        GetShapeType = msoShapeRoundedRectangle     ' 角丸（処理）
    Else
        GetShapeType = msoShapeRectangle            ' 長方形（標準）
    End If
End Function

' 依存関係から階層（レベル）を割り当てる簡易アルゴリズム
Private Function CalculateNodeLevels(ByRef dictNodes As Object, ByRef nodeConnections As Collection) As Object
    Dim levels As Object
    Set levels = CreateObject("Scripting.Dictionary")

    Dim key As Variant
    For Each key In dictNodes.Keys
        levels(CStr(key)) = 0
    Next key

    Dim i As Long, conn As Variant
    ' 最大N回ループさせて階層を押し下げる
    For i = 1 To dictNodes.Count
        For Each conn In nodeConnections
            Dim fromLvl As Long, toLvl As Long
            fromLvl = levels(conn("from"))
            toLvl = levels(conn("to"))

            If toLvl <= fromLvl Then
                levels(conn("to")) = fromLvl + 1
            End If
        Next conn
    Next i

    Set CalculateNodeLevels = levels
End Function

