#target photoshop  
//var foregroundColor = app.foregroundColor;  
//var backgroundColor = app.backgroundColor;  
//alert ("foregroundcolor\n"+foregroundColor.rgb.red+"\n"+foregroundColor.rgb.green+"\n"+foregroundColor.rgb.blue);  
//alert ("backgroundcolor\n"+backgroundColor.rgb.red+"\n"+backgroundColor.rgb.green+"\n"+backgroundColor.rgb.blue);  

var str = "Player 1";

var b = new File("/Users/James/Documents/player.txt");
b.open("w", "TEXT");
b.write(str);