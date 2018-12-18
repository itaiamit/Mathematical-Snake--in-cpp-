Itai Amit 204660989
Gil Reuven 206348948

Notes:

*There are sounds inside the game.

To hear them follow these steps:
1) Open the project.
2) Right click on "Snake" project on the right hand side.
3) Go to "Properties".
4) Click on "Linker" --> "Input".
5) Click the arrow on the right side of "Additional Dependencies" --> "Edit".
6) Inside the top box write "winmm.lib". Click "OK" and you're all set.
Link to download sounds: https://drive.google.com/drive/folders/0BwVdhp2hSe-YZzNVV1d5M3dVVDA?usp=sharing

*Run the game on a 25x80 console (The game itself runs at 24x80 as requested).

*If a snake has gotten into a loop with himself - We chose to reset it to a single character.
At the beggining of the new mission he will be the same size as he was, though.

*If a bullet of snake#1 crashed in a bullet of snake#2, they are both disappear and non of the snakes get another bullet.

*Same thing if both bullets are belong to the same snake.

הערות לתרגיל 3:
*בתיקייה "Snake" ישנו קובץ בשם "missions.txt" אשר ממנו נקראות המשימות למשחק.
בנוסף, קיים קובץ "all missions.txt" שבו גם קיימות כל המשימות לשם גיבוי (אם תרצי למחוק ולנסות דברים).
