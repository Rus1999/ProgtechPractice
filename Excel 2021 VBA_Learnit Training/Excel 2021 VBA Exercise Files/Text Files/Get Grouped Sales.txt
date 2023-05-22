Sub GetGroupedSales()
    Select Case Sales
        Case "Salesperson"
            PageName = "Salesperson"
            RowName = "Year"
            ColumnName = "Make"
            DataName = "Selling Price"
        Case "Model"
            PageName = "Model"
            RowName = "Year"
            ColumnName = "Color"
            DataName = "Color"
        Case "Classification"
            PageName = "Classification"
            RowName = "Make"
            ColumnName = "Year"
            DataName = "Selling Price"
    End Select

End Sub
