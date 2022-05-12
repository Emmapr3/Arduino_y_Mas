# Arduino y Más
**Vista general**
-  [Descripción](#descripción)
-  [Sensores y componentes](#sensores-y-componentes)
-  [Incubadora de Huevos](#incubadora-de-huevos)
-  [Espectrómetro de Fourier](#espectrómetro-de-fourier)


## Descripción
Este repositorio contiene una serie de archivos con Código Fuente que son utilizados para implementar diversos tipos de sensores analógicos y digitales con la tarjeta [Arduino](https://www.arduino.cc/) (microcontrolador ATmega328p) y [tarjetas similares](https://www.adafruit.com/product/1044).

Cada código contiene una descripción detallada de lo que se pretende hacer con la tarjeta Arduino y los componentes utilizados. En esta serie de archivos podrá ver la utilidad de una diversidad de sensores analógicos que tienen distintos fines, así como un par de proyectos interesantes que conjuntan dichos sensores para crear instrumentación útil.

## Sensores y componentes
En esta serie de códigos fuente para Arduino, puede encontrar una diversidad de sensores y componentes que son utilizados para distintos fines, como se alista a continuación:

-   Push Botton ([Dos botones con presion mantenida](Dos_Botones+Presion_Mantenida.ino), [Multiboton con un pin](Multiboton_Un_Pin.ino))
-   Buzzer ([Bocina con 3 tonos](Bocina_3Tonos.ino))
-   Potenciómetro: [Lectura de multiples potenciómetros](Dos_Potenciometros.ino)
-   LEDs: [una frecuencia](LCD+Temperatura+IndicadorLED.ino) y [RGB](LED_RGB+Potenciometros.ino)
-   Pantalla LCD: [Reloj editable](Reloj_Editable_con_Arduino.ino) y [muestra de lecturas](LCD+Temperatura.ino)
-   Rele mecánico ([Control de temperatura con Rele](LCD+Temperatura+IndicadorRele.ino))
-   Encoder rotativo ([Interrupción Encoder](Interrupcion_Encoder.ino))
-   Joystick ([Joystick con Arduino](Joystick_con_Arduino.ino))
-   Motor DC: [Motor DC con control PID](PID_MotorDC_Position.ino) y [Velocidad de motor DC con Encoder](Velocidad_MotorDC+Encoder.ino)
-   Servomotor ([Control de servomotor](ServoMotor.ino))
-   Sensor de temperatura: [Termómentro con Arduino](Termometro_con_Arduino.ino)
-   Sensor de distacia: [sensor ultrasónico](SensorUltrasonico+MotorDC.ino) 
-   Sensor Infrarrojo: [Optointerruptor en IR](Optointerruptor_en_Infrarrojo.ino)
-   Sensor de presión: [módulo FSR](Caracterizacion_FSR.ino)
-   Sensor de luz: [sensor de intensidad de luz](Sensor_Intensidad_Luz.ino)

-   Comunicación serial: [lectura de Monitor Serie](Dos_Potenciometros.ino) y [Serial Plotter](Multiplotter_SerialPlotter.ino) para el IDE de Arduino 
-   Comunicación Bluetooth: [Módulo bluetooth y comunicación serial](Serial_Event_from_App+Bluetooth.ino) 
-   Guardar Información: [Escritura en memoria SD](Temperatura+Tiempo+SDCard.ino)

## Incubadora de Huevos
Como su nombre lo dice, [este proyecto](Incubadora_de_Huevos.ino) consta de realizar una incubadora de huevos a partir de componentes electrónicos que son conectados a un Arduino. La idea es mantener una temperatura estable dentro de un recipiente de tamaño pequeño (Hielera de unicel de 30x40x30 cm).

Aquí, se implementan sensores analógicos de temperatura, así como resistencias de potencia cerámicas y un ventilador para mantener la temperatura constante dentro del recipiente mediante con control PID. Además, se realizó una Aplicación para teléfono móvil (App, [archivo apk](ControlTemperatura.apk)) para definir la temperatura deseada para el recipiente y tener la lectura en tiempo real de la misma.

La App se realizó en la plataforma de [App Inventor](http://ai2.appinventor.mit.edu/) y se mantuvo comunicación con los componentes de la incubadora mediante comuinicación Bluetooth.

La Incubadora es capaz de mantener una temperatura constante entre los 25°C y los 38°C, debido a los componentes que se utilizaron para generar los cambios de temperatura. Es posible mejorar este rango de temperatura cambiando dichos componentes: resistencias de potencia para aumentar la temperatura y el cooler de computadora para disminuirla al interior del recipiente.
También, es posible añadir un humificador y sensor de humedad para controlar esta variable física dentro de la Incubadora.


## Espectrómetro de Fourier
La carpeta [Espectrómetro_Fourier](Espectrometro_Fourier) contiene los archivos correspondientes a una propuesta de proyecto para realizar un Espectrómetro de Fourier con la tecnología de Arduino. Este dispositivo está planeteado para ser utilizado en un laboratorio de óptica para investigación y desarrollo.

Por una parte, se tiene el código fuente para un Microcontrolador [Teensy 3.0](https://learn.adafruit.com/fft-fun-with-fourier-transforms/hardware) con el cuál se toma la señal de franjas que genera un prisma cristalino y hace la transformada rápida de Fourier (fft) en tiempo real para pasar dichos datos a una interfaz gráfica. La interfaz gráfica se realizó en Python, donde se muestra es espectro de frecuencias que genera el microcontrolador con la fft. De este modo, es posible obtener el espectro generado del experimento en cuestión de segundos.
