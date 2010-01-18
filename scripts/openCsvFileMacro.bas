REM  *****  BASIC  *****

Sub Main

End Sub


sub CopyContent
rem ----------------------------------------------------------------------
rem define variables
dim document   as object
dim dispatcher as object
rem ----------------------------------------------------------------------
rem get access to the document
document   = ThisComponent.CurrentController.Frame
dispatcher = createUnoService("com.sun.star.frame.DispatchHelper")

rem ----------------------------------------------------------------------
dim args1(0) as new com.sun.star.beans.PropertyValue
args1(0).Name = "ToPoint"
args1(0).Value = "A1:cw43"

dispatcher.executeDispatch(document, ".uno:GoToCell", "", 0, args1())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Copy", "", 0, Array())


end sub

sub OpenFile
rem ----------------------------------------------------------------------
rem define variables
dim document   as object
dim dispatcher as object
rem ----------------------------------------------------------------------
rem get access to the document
document   = ThisComponent.CurrentController.Frame
dispatcher = createUnoService("com.sun.star.frame.DispatchHelper")

rem ----------------------------------------------------------------------
rem dispatcher.executeDispatch(document, ".uno:Open", "", 0, Array())
ShExec = createUnoService("com.sun.star.system.SystemShellExecute")
ShExec.execute("/home/hector/projects/GenomAMf/dq_iteration_values.csv", "", 0)

end sub

Sub openCsv
oDesktop = createUnoService("com.sun.star.frame.Desktop")
sUrl = convertToUrl("/home/hector/projects/eclipse/GenomAMf/data/dq_iteration_values.csv")
'sUrl = convertToUrl("/home/hector/test.csv")
Dim mFileProperties(1) As New com.sun.star.beans.PropertyValue 
mFileProperties(0).Name = "FilterName"
mFileProperties(0).Value = "scalc: Text - txt - csv (StarCalc)"
mFileProperties(1).Name = "FilterFlags"

Dim columnsOptions as String
nColumns = 43

Dim i
For i = 1 To nColumns
  columnsOptions = columnsOptions + (i - 1) + "/10"
  If i <> nColumns Then
    columnsOptions = columnsOptions + "/"
  End If
Next i

mFileProperties(1).Value = "59/9,34,76,1," & columnsOptions

Dim document as Object
Dim dispatcher as Object
oDocument = oDesktop.loadComponentFromURL(sUrl,"_blank",0,mFileProperties())

dim args1(0) as new com.sun.star.beans.PropertyValue
args1(0).Name = "ToPoint"
'args1(0).Value = "A1:cw43"
args1(0).Value = "A1:AQ101"
document   = oDocument.CurrentController.Frame
dispatcher = createUnoService("com.sun.star.frame.DispatchHelper")
dispatcher.executeDispatch(document, ".uno:GoToCell", "", 0, args1())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Copy", "", 0, Array())
End Sub 