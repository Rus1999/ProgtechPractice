Function GetModel(VinNum)
Dim ModelMarker As String
ModelMarker = Mid(VinNum, 3, 2)
Select Case ModelMarker
Case 16
GetModel = "Caterra"
Case 17
GetModel = "Seville"
Case 20
GetModel = "Sierra 2500"
Case 21
GetModel = "Safari"
Case 35
GetModel = "Bonneville"
Case 38
GetModel = "Grand Prix"
Case 44
GetModel = "Intrigue"
Case 45
GetModel = "Bravada"
Case 59
GetModel = "F-1500"
Case 62
GetModel = "Century"
End Select
End Function
