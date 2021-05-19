# CoolPrintf
New realization of the printf function.

>**Before the arrows, the new function is located,coolPrintf
and on the right - is the original printf function.**


coolPrintf ( …. );  | printf ( …. );
------------- | -------------
'-10'         |'-10'
'-  10'       |'-  10'
'-10  '       |'-10  '
'-0010'       |'-0010'
'-  10'       |'  -10'
'-10  '       |'-10  '
'-10'         |'-10'
'-10'         |'4294967286'
------------- | -------------
%             |%          
'23161'       |'23161'   
'a2c12'       |'a2c12' 
'K'           |'K'      
------------- | -------------
'Hello'       |'Hello'     
'     Hello'  |'     Hello' 
'Hello     '  |'Hello     ' 
------------- | -------------
'10.345600'   |'10.345600'  
'10.3'        |'10.3'    
'10.35'       |'10.35'    
'   10.35'    |'   10.35'  
' 10.3456'    |' 10.3456'  
'00010.35'    |'00010.35'  
'10.35'       |'10.35'    
'1234567.35'  |'1234567.35' 
