### 2022-2 Advanced Embedded Systems Term-Project
  
## [ Reflexes Game ]   

**GAME MODE**
  > GAME 1 - Click Number   
  > GAME 2 - Match Area   
   
**H/W**
  > Raspberry Pi 4B   
  > 4x4 Switch   
  > 8x8 Dot Matrix (MAX7219)   
  > LCD   
   
**Interface**
  > GPIO   
  > SPI - Dot Matrix   
  > I2C - LCD   
   
**S/W**  ` language: C `   
  > main   
  > switch, dotmatrix, lcd   

   
### make   
```
make
```
or
```
gcc -c -o main.o main.c
gcc -c -o switch.o switch.c
gcc -c -o dotmatrix.o dotmatrix.c
gcc -c -o lcd.o lcd.c
gcc -o final main.o switch.o dotmatrix.o lcd.o -lwiringPi -lbcm2835
```


### execute   
```
sudo ./final
```


### clean   
```
make clean
```

---

## [ Result ]

**GAME 1**   
![image](https://user-images.githubusercontent.com/96249554/208507512-f3ef427d-5b98-47db-bbe8-3a3dfeb4db9a.png)
   
**GAME 2**   
![image](https://user-images.githubusercontent.com/96249554/208507612-cf29f30e-44f6-4d41-a221-fd17d42ffd28.png)

---

## [ Video ]   

**GAME 1**   

https://user-images.githubusercontent.com/96249554/208508351-be9ecb30-44b5-4455-9369-8c5078d10ac3.mp4

**GAME 2**   

https://user-images.githubusercontent.com/96249554/208508395-3ee80c32-41a1-4fb6-aaf7-83675b218c46.mp4


