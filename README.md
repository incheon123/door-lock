# 도어락

stm32f103RB 보드와 1602 i2c lcd, 숫자 키패드를 이용한 도어락

# 개발 하드웨어

+ stm32f103RB
+ 1602 i2c lcd
+ NT-207NN-WB(키패드)
+ usb mini-b 케이블
+ female to male cable * 11개

# 개발 기간

+ 2024.09.01 ~ 2024.10.30
+ 개발 하드웨어 구매
+ 개발
+ 테스트

# 개발환경 및 기술스택

+ 윈도우
+ STM32CubeIDE
+ c언어
+ Serial 통신(i2c)

# 사용 방법

1. stm32CubeIDE 설치
2. 개발 하드웨어 구매
3. + 1602 i2c lcd SDA - stm32f103RB SDA
   + 1602 i2c lcd SCL - stm32f103RB SCL
   + 키패드(왼쪽부터) - stm32f103RB D2 ~ D9
