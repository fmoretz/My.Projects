Attribute VB_Name = "Modulo1"
Sub Arrenhius()

    Dim k As Double
    Dim A As Double
    Dim Ea As Double
    Dim R As Double
    Dim T As Double
    
    A = Range("A2")
    Ea = Range("B2")
    R = Range("C2")
    T = Range("D2")
    
    k = A * Exp(-Ea / (R * T))
    
    ActiveSheet.Range("E2") = k
    
End Sub
