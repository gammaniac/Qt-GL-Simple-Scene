  ____                _______      
 / __ \___  ___ ___  / ___/ /   
/ /_/ / _ \/ -_) _ \/ (_ / /__  
\____/ .__/\__/_//_/\___/____/  
    /_/  

This small program is the result of my experimenting on getting the latest Qt 5.0.1 to play nice with modern OpenGL 4.3. The program uses a Qt interface with 3 buttons and a rendering panel. Two different models are stored as index buffer objects and they can be switched on the fly using the button "switch buffer". The button labeled "toggle animation" toggles rotation about the z-axis. The last button labeled "screen shot" takes a screen shot of the rendering panel and drops it as a .png file in the current directory. I have used the latest version of Qt 5.0.1 and the latest OpenGL implementation 4.3 core. I'm sure it could be ported to earlier versions of both OpenGL and Qt but I have no interest in doing this. To compile, use QMake on the command line. 