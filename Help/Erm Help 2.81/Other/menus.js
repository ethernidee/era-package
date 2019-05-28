<!--
function makemenu(page, letters)
{
 var allletters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ".split('');
 var z = "";
 var fond = "../images/fond.gif"
 for(i=0;i<=27;i++)
 {
  if (i%2==0) 
   document.write("<tr>");
  z=(letters.indexOf(allletters[i],0)!=-1)?("<a class=menu href='"+page+"#"+allletters[i]+"'>"+allletters[i]+"</a>"):"&nbsp;";
  document.write("<td background='"+fond+"' align=center>"+z+"</td>");
  if(i%2==1) 
   document.write("</tr>");
 }
}
-->