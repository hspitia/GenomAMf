REM  *****  BASIC  *****

Sub Main

End Sub



sub Formula
rem ----------------------------------------------------------------------
rem define variables
dim document   as object
dim dispatcher as object
rem ----------------------------------------------------------------------
rem get access to the document
document   = ThisComponent.CurrentController.Frame
dispatcher = createUnoService("com.sun.star.frame.DispatchHelper")

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:InsertObjectStarMath", "", 0, Array())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Escape", "", 0, Array())

rem ----------------------------------------------------------------------
dim args3(1) as new com.sun.star.beans.PropertyValue
args3(0).Name = "Count"
args3(0).Value = 1
args3(1).Name = "Select"
args3(1).Value = false

dispatcher.executeDispatch(document, ".uno:GoRight", "", 0, args3())
end sub


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


Sub openCsv
oDesktop = createUnoService("com.sun.star.frame.Desktop")
sUrl = convertToUrl("/home/hspitia/projects/GenomAMf/data/dq_iteration_values.csv")
'sUrl = convertToUrl("/home/hector/test.csv")
Dim mFileProperties(1) As New com.sun.star.beans.PropertyValue 
mFileProperties(0).Name = "FilterName"
mFileProperties(0).Value = "scalc: Text - txt - csv (StarCalc)"
mFileProperties(1).Name = "FilterFlags"

Dim columnsOptions as String
nColumns = 44

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
args1(0).Value = "A1:AQ301"
document   = oDocument.CurrentController.Frame
dispatcher = createUnoService("com.sun.star.frame.DispatchHelper")
dispatcher.executeDispatch(document, ".uno:GoToCell", "", 0, args1())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Copy", "", 0, Array())
End Sub 


sub pasteCsvContent
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
args1(0).Value = "$Q$5"

dispatcher.executeDispatch(document, ".uno:GoToCell", "", 0, args1())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Paste", "", 0, Array())


end sub

Sub openCsvRegrerssion
oDesktop = createUnoService("com.sun.star.frame.Desktop")
sUrl = convertToUrl("/home/hspitia/projects/GenomAMf/data/regression_values_for_plot.csv")
'sUrl = convertToUrl("/home/hector/test.csv")
Dim mFileProperties(1) As New com.sun.star.beans.PropertyValue 
mFileProperties(0).Name = "FilterName"
mFileProperties(0).Value = "scalc: Text - txt - csv (StarCalc)"
mFileProperties(1).Name = "FilterFlags"

Dim columnsOptions as String
nColumns = 44

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
args1(0).Value = "A2:L259"
document   = oDocument.CurrentController.Frame
dispatcher = createUnoService("com.sun.star.frame.DispatchHelper")
dispatcher.executeDispatch(document, ".uno:GoToCell", "", 0, args1())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Copy", "", 0, Array())
End Sub 


sub pasteCsvContentRegrerssion
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
args1(0).Value = "$A$4"

dispatcher.executeDispatch(document, ".uno:GoToCell", "", 0, args1())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Paste", "", 0, Array())


end sub


sub copySheetToNewDoc
rem ----------------------------------------------------------------------
rem define variables
dim document   as object
dim dispatcher as object
rem ----------------------------------------------------------------------
rem get access to the document
document   = ThisComponent.CurrentController.Frame
dispatcher = createUnoService("com.sun.star.frame.DispatchHelper")

rem ----------------------------------------------------------------------
dim args1(2) as new com.sun.star.beans.PropertyValue
args1(0).Name = "DocName"
args1(0).Value = ""
args1(1).Name = "Index"
args1(1).Value = 32767
args1(2).Name = "Copy"
args1(2).Value = true

dispatcher.executeDispatch(document, ".uno:Move", "", 0, args1())


end sub

Sub openCsvDqValues
oDesktop = createUnoService("com.sun.star.frame.Desktop")
sUrl = convertToUrl("/home/hspitia/DqValues.csv")
'sUrl = convertToUrl("/home/hector/test.csv")
Dim mFileProperties(1) As New com.sun.star.beans.PropertyValue 
mFileProperties(0).Name = "FilterName"
mFileProperties(0).Value = "scalc: Text - txt - csv (StarCalc)"
mFileProperties(1).Name = "FilterFlags"

Dim columnsOptions as String
nColumns = 44

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
args1(0).Value = "B5:AP22"
document   = oDocument.CurrentController.Frame
dispatcher = createUnoService("com.sun.star.frame.DispatchHelper")
dispatcher.executeDispatch(document, ".uno:GoToCell", "", 0, args1())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Copy", "", 0, Array())
End Sub 


sub pasteCsvContentDqValues
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
args1(0).Value = "$B$2"

dispatcher.executeDispatch(document, ".uno:GoToCell", "", 0, args1())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Paste", "", 0, Array())


end sub

sub pasteCsvContentDqValuesBottom
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
args1(0).Value = "$B$30"

dispatcher.executeDispatch(document, ".uno:GoToCell", "", 0, args1())

rem ----------------------------------------------------------------------
dispatcher.executeDispatch(document, ".uno:Paste", "", 0, Array())


end sub

