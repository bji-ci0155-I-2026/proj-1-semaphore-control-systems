# proj-1-semaphore-control-systems

## Proyecto #1 - Sistemas de control de semáforos

Universidad de Costa Rica - Sistemas Empotrados de Tiempo Real - CI-0155

**Integrantes:** 
- Isabella Rodríguez Sánchez (C26701)
- Esteban Isaac Baires Cerdas (C10844)
- Jorge Ricardo Díaz Sagot (C12565)

---

## 1. Semáforo por tiempo fijo

### Investigación

Este tipo de semáforo es de los más sencillos. Funciona con ciclos de colores en tiempos configurados previamente. 

Por ejemplo, está en rojo por 5 minutos antes de cambiar a verde por otros 5 minutos.

**Características**:
- Este tipo de semáforo no depende de sensores o inputs de ningún tipo. 
- Se puede aplicar para semáforos de tránsito y peatonales. En este caso, al añadir sonido antes de pasar a verde, sería más útil para los peatones.

> **En Semáforos de tiempo fijo:** Los semáforos de tiempo fijo se utilizan en aquellas intersecciones donde el comportamiento de tránsito es estable, es decir donde los flujos vehiculares se pueden adaptar a un programa de tiempos previsto, sin ocasionar demoras o congestionamiento excesivo. Los semáforos de tiempo fijo, se adaptan fácilmente a aquellas ocasiones en que queremos coordinar varias intersecciones a lo largo de un corredor vehicular [2].

**Casos de uso:**

**Ventajas:**

**Desventajas:**

### Descripción de la arquitectura

TODO: Indicar la arquitectura utilizada, incluyendo:
- Entradas
- Salidas
- Unidad de procesamiento central
- Comunicación

### Implementación del sistema empotrado

Para utilizar desde su SimulIDE debe:
1. Abrir el archivo .sim1 del mismo repositorio.
2. Activar la simulación.

#### SimulIDE

Archivo de simulación: [semaphore-fixed-time.sim1](./simul/semaphore-fixed-time.sim1).
- Cargado con el .hex en `../code/semaphore-fixed-time/build/arduino.avr.uno/semaphore-fixed-time.ino.hex`

Ver video de simulación en SimulIDE: [semaphore-fixed-time-simul.mp4](./media/semaphore-fixed-time-simul.mp4).

#### Kit de Arduino Uno R3

Código fuente: [semaphore-fixed-time.ino](./code/semaphore-fixed-time/semaphore-fixed-time.ino).

Ver video de prueba: [semaphore-fixed-time.mp4](./media/semaphore-fixed-time.mp4).

TODO: Proveer un esquemático con las conexiones realizadas.

---

## 2. Semáforo "peatonal" con interrupción por botón

### Investigación

Los pasos peatonales y semáforos peatonales no son más que una medida de tráfico para mejorar la seguridad de los peatones al cruzar calles.

Según el blog [1] hay semáforos peatonales que se activan sólo y cuando una persona presiona el botón. Por lo general estos semáforos tienen las siguientes características:

- No tienen un ciclo fijo programado.
- Se activan sólo y cuando una persona presiona el botón.
- Son usados en lugares que no hay un volumen grande de tráfico vehicular.
- Pueden durar hasta 2 minutos en activar el paso a peatones(semáforo peatonal en verde y semáforo vehicular en rojo).
- Suelen emitir una señal de sonido para personas con discapacidad visual.
- Suelen incluir el tiempo de espera en el semáforo peatonal.

TODO: Listar diferencias y ventajas/desventajas de este tipo de semáforo.

### Descripción de la arquitectura

TODO: Indicar la arquitectura utilizada, incluyendo:
- Entradas
- Salidas
- Unidad de procesamiento central
- Comunicación

### Implementación del sistema empotrado

Para utilizar desde su SimulIDE debe:
1. Abrir el archivo .sim1 del mismo repositorio.
2. Activar la simulación.

#### SimulIDE

Archivo de simulación: [semaphore-interrupt-button-vehicle.sim1](./simul/semaphore-interrupt-button-vehicle.sim1).
- Cargado con el .hex en `../code/semaphore-interrupt-button-vehicle/build/arduino.avr.uno/semaphore-interrupt-button-vehicle.ino.hex`

Ver video de simulación en SimulIDE: [semaphore-interrupt-button-vehicle-simul.mp4](./media/semaphore-interrupt-button-vehicle-simul.mp4).

#### Kit de Arduino Uno R3

Códigos fuente:
- Semáforo vehicular: [semaphore-interrupt-button-vehicle.ino](./code/semaphore-interrupt-button-vehicle/semaphore-interrupt-button-vehicle.ino).
- Semáforo peatonal: [semaphore-interrupt-button-peatonal.ino](./code/semaphore-interrupt-button-peatonal/semaphore-interrupt-button-peatonal.ino).

Ver video de prueba vehicular: [semaphore-interrupt-botton.mp4](./media/semaphore-interrupt-botton.mp4).

TODO: Proveer un esquemático con las conexiones realizadas.

---

## 3. Semáforo inteligente con interrupción por sensor

### Investigación

Los semáforos integrados con detección de peatones son una solución avanzada diseñada para **optimizar la eficiencia del tráfico** y **reducir las infracciones de luz roja** en las intersecciones urbanas. Estos sistemas combinan tecnología de detección, control inteligente y retroalimentación en tiempo real para lograr un flujo vehicular más seguro y predecible.

A continuación, se resumen sus características y beneficios principales:

#### Mejora de la eficiencia del tráfico
Estos semáforos no funcionan con ciclos estáticos, sino que utilizan mecanismos de **tiempo adaptativo**.
*   **Detección en tiempo real:** Mediante cámaras y sensores, identifican la presencia de peatones en los cruces.
*   **Ajuste dinámico:** Las fases verdes se amplían o acortan según el flujo de peatones detectado, lo que minimiza las esperas innecesarias para los vehículos.
*   **Priorización del movimiento:** Al reducir el tiempo de inactividad, se evitan cuellos de botella y se genera un flujo vehicular más fluido.

#### Reducción de infracciones y mejora de la seguridad
El sistema aborda la seguridad mediante un **monitoreo automatizado** constante.
*   **Detección de cruces ilegales:** El sistema captura instancias de peatones que cruzan durante la fase de luz roja.
*   **Alertas audiovisuales:** Se emiten avisos inmediatos para advertir a conductores y peatones sobre comportamientos inseguros.
*   **Recopilación de evidencia:** Utilizan videos de alta definición y datos de sensores para documentar las infracciones sin necesidad de supervisión manual constante.

#### Tecnología y Algoritmos Inteligentes
Para garantizar un rendimiento confiable, estos sistemas emplean **algoritmos de aprendizaje automático** que procesan datos de múltiples sensores. Estos algoritmos permiten:
*   Detectar comportamientos complejos en diversas condiciones de clima e iluminación.
*   Reducir falsos positivos causados por sombras o reflejos.
*   Tener una **respuesta predictiva**, anticipando el movimiento de los peatones para ajustar las señales de forma proactiva.

#### Interacción con el usuario y mantenimiento 
*   **Pantallas de cuenta regresiva:** Incluyen indicadores LED que informan el tiempo restante para cruzar, lo que reducen el pánico en peatones y ayuda a los conductores a ajustar su velocidad. 
*   **Ventajas operativas:** Funcionan de forma automatizada las 24 horas del día. Además, permiten la **configuración remota** de los parámetros y cuentan con componentes duraderos con protección contra sobretensiones, lo que reduce los costos y la frecuencia de mantenimiento.

TODO: Listar diferencias y ventajas/desventajas de este tipo de semáforo.

### Descripción de la arquitectura

TODO: Indicar la arquitectura utilizada, incluyendo:
- Entradas
- Salidas
- Unidad de procesamiento central
- Comunicación

### Implementación del sistema empotrado

Para utilizar desde su SimulIDE debe:
1. Abrir el archivo .sim1 del mismo repositorio.
2. Activar la simulación.

#### SimulIDE

Archivo de simulación: [semaphore-interrupt-sensor.sim1](./simul/semaphore-interrupt-sensor.sim1).
- Cargado con el .hex en `../code/semaphore-interrupt-sensor/build/arduino.avr.uno/semaphore-interrupt-sensor.ino.hex`

Ver video de simulación en SimulIDE: [semaphore-interrupt-sensor-simul.mp4](./media/semaphore-interrupt-sensor-simul.mp4).

#### Kit de Arduino Uno R3

Código fuente: [semaphore-interrupt-sensor.ino](./code/semaphore-interrupt-sensor/semaphore-interrupt-sensor.ino).

Ver video de prueba: [semaphore-interrupt-sensor.mp4](./media/semaphore-interrupt-sensor.mp4).

---

## Referencias

> **Aclaración sobre el uso de la Inteligencia Artificial:**
> Para la estructuración, corrección de estilo y formato Markdown de este documento, se utilizó como asistencia un asistente de desarrollo con Inteligencia Artificial.

[1] K. Behrens, "Do Crosswalk Buttons Actually Work?," Pelco, 15-mar-2026. [En línea]. Disponible: https://www.pelcoinc.com/blog/do-crosswalk-buttons-actually-work. [Accedido: 21-mar-2026].

[2] Ministerio de Obras Públicas y Transportes (MOPT), "Semáforos". [Online]. Available: https://repositorio.mopt.go.cr/server/api/core/bitstreams/90d07687-b340-4304-945b-acb89ec9cf78/content.

[3] Yangzhou FAMA Intelligent Equipment Co., Ltd. (2024). Cómo los semáforos integrados con detección de peatones mejoran la eficiencia del tráfico en las intersecciones y reducen las infracciones de luz roja. FAMA Traffic. Disponible: https://es.fama-tech.com/industry/how-pedestrian-detection-integrated-traffic-lights-improve-intersection-traffic-efficiency-and-reduce-red-light-violations.html

[4] Arduino Project Hub. "Use a buzzer module / piezo speaker using Arduino UNO." Disponible en: https://projecthub.arduino.cc/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-cf4191

[5] Arduino Project Hub. "Ultrasonic sensor with Arduino - complete guide." Disponible en: https://projecthub.arduino.cc/lucasfernando/ultrasonic-sensor-with-arduino-complete-guide-284faf

[6] arashjafari/audio-to-arduino. Disponible en: https://github.com/arashjafari/audio-to-arduino
