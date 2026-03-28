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

Seguidamente se especifican los casos de uso, ventajas y desventajas de los semáforos de tiempo fijo segun [7]:

**Casos de uso:**
- Intersecciones aisladas con demanda estable; calles con flujos previsibles.
- Corredores coordinados donde se busca progresión vehicular.
- Zonas con infraestructura de detección limitada o sin detectores vehiculares.
- Cruces peatonales con horarios fijos (zonas escolares, centros comerciales).
- Entornos donde la seguridad prioriza ciclos constantes (reducción de conflictos en ángulos).

**Ventajas :**
- **Simplicidad de diseño**: fácil implementación; bajo costo de operación.
- **Permite coordinación** entre intersecciones; mejora la fluidez en intersecciones con flujos vehiculares estables.
- **Baja complejidad tecnológica**: no tiene sensores y no necesita mucha potencia del microcontrolador.

**Desventajas:**
- **No se adapta** a variaciones de demanda puede generar demoras innecesarias.
- **Menor eficiencia** que sistemas actuados o inteligentes.
- **Programación rígida** para cambios en los tiempos ante cambios en el flujo vehicular.

### Descripción de la arquitectura

La arquitectura implementada para este semáforo de tiempo fijo es la más sencilla de todas:
- **Entradas**: Ninguna. El semáforo opera de manera autónoma utilizando temporizadores explícitos (`delay()`), sin entradas del entorno (lazo abierto).
- **Salidas**: Tres (3) salidas digitales del microcontrolador hacia los leds de cada color del semaforo:
  - `Pin 2`: LED Rojo (estado de parada).
  - `Pin 4`: LED Amarillo (estado de precaución).
  - `Pin 7`: LED Verde (estado de avance).
- **Unidad de procesamiento central**: Arduino Uno R3 es el que ejecuta cíclicamente el bucle lógico configurando los pines de salida en HIGH y LOW mediante programación en Arduino IDE.
- **Comunicación**: No se implementan protocolos de comunicación serial ni redes externas. El sistema solo depende de conexion a energia por cable o bateria.

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

Ahora se especifican las diferencias, ventajas y desventajas de los semáforos con interrupción por botón [1][8]:

**Diferencias respecto al de tiempo fijo:**

- Introduce interacción del usuario (botón).
- No sigue un ciclo completamente automático.
- Responde a demanda puntual en lugar de tiempo predefinido.

**Ventajas:**

- **Activación bajo demanda:** el sistema solo cambia cuando un peatón lo solicita, reduciendo interrupciones innecesarias al tráfico vehicular.
- **Mejora la seguridad peatonal:** proporciona un cruce controlado, disminuyendo el riesgo de accidentes.
- **Mayor eficiencia** que el tiempo fijo en zonas con baja demanda peatonal, al evitar ciclos innecesarios.
- **Costo moderado:** requiere únicamente un pulsador e implementación de interrupciones, sin necesidad de sensores complejos.

**Desventajas:**

- **Dependencia del usuario:** si el peatón no presiona el botón, el sistema no se activa.
- **Tiempo de espera:** puede existir un retardo antes de habilitar el cruce peatonal.
- **No detecta automáticamente la demanda:** menor eficiencia comparado con sistemas con sensores.
- **Adaptabilidad limitada:** no considera condiciones dinámicas del tráfico vehicular.


### Descripción de la arquitectura

La arquitectura del semáforo peatonal con interrupción por botón es la siguiente:

- **Entradas**: Una (1) entrada digital hacia el microcontrolador:
  - `Pin 10` (BUTTON): Pulsador/botón que el peatón presiona para solicitar el cruce. El microcontrolador lee su estado con `digitalRead()` en el bucle principal.
- **Salidas**: Cuatro (4) salidas digitales del microcontrolador:
  - `Pin 2`: LED Rojo (estado de parada vehicular / cruce peatonal activo).
  - `Pin 4`: LED Amarillo (estado de precaución / transición).
  - `Pin 7`: LED Verde (estado de circulación vehicular / espera peatonal).
  - `Pin 9`: Buzzer piezoeléctrico (señal sonora de cuenta regresiva para peatones con discapacidad visual).
- **Unidad de procesamiento central**: Arduino Uno R3 que ejecuta el bucle principal de polling sobre el botón y, al detectar la señal, invoca la rutina `allow_pedestrians()` que gestiona la secuencia de cambio de fases mediante `delay()`.
- **Comunicación**: No se implementan protocolos de comunicación serial ni redes externas. El sistema opera de forma autónoma y solo depende de conexión a energía por cable o batería.

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

Ver video de prueba vehicular: [semaphore-interrupt-botton.mp4](./media/semaphore-interrupt-botton.mp4).

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

Resumiendo sus diferencias, ventajas y desventajas [3][8]: 

**Diferencias respecto a los semáforos anteriores:**

- Usa sensores en lugar de interacción manual.
- Toma decisiones automáticas basadas en datos en tiempo real.
- Puede implementar lógica adaptativa o inteligente.


**Ventajas:**

- **Alta adaptabilidad:** ajusta los tiempos en función de la demanda en tiempo real.
- **Optimización del flujo vehicular:** reduce demoras y congestión al minimizar tiempos muertos.
- **Mayor seguridad:** detecta presencia de peatones y puede generar alertas preventivas.
- **Automatización completa:** no depende de la interacción del usuario.
- **Escalabilidad:** puede integrarse con sistemas de control urbano e IoT.

**Desventajas:**

- **Alto costo inicial:** requiere sensores, procesamiento adicional y posible infraestructura de comunicación.
- **Mayor complejidad técnica:** implementación, calibración y programación más avanzadas.
- **Mantenimiento especializado:** los sensores pueden fallar o requerir ajustes periódicos.
- **Posibles errores de detección:** falsos positivos o negativos afectan el rendimiento del sistema.

### Descripción de la arquitectura

La arquitectura del semáforo inteligente con interrupción por sensor es la siguiente:

- **Entradas**: Dos (2) entradas digitales hacia el microcontrolador:
  - `Pin 13` (ECHO): Señal de retorno del sensor ultrasónico HC-SR04. El microcontrolador mide con `pulseIn()` el tiempo del pulso de eco para calcular la distancia al objeto/peatón.
  - `Pin 12` (BUTTON): Pulsador/botón de respaldo para activación manual del ciclo peatonal.
- **Salidas**: Cinco (5) salidas digitales del microcontrolador:
  - `Pin 7`: LED Rojo (estado de parada vehicular / cruce peatonal activo).
  - `Pin 4`: LED Amarillo (estado de precaución / transición).
  - `Pin 2`: LED Verde (estado de circulación vehicular / espera peatonal).
  - `Pin 6`: Buzzer piezoeléctrico (señal sonora de cuenta regresiva para peatones con discapacidad visual).
  - `Pin 10` (TRIGGER): Pulso de disparo del sensor ultrasónico HC-SR04 (señal de 10 µs enviada para iniciar la medición de distancia).
- **Unidad de procesamiento central**: Arduino Uno R3 que en cada iteración del bucle principal envía el pulso TRIGGER, mide el tiempo del ECHO, calcula la distancia con la fórmula `(duration × 0.0343) / 2` (donde 0.0343 cm/µs es la velocidad del sonido a temperatura ambiente y la división entre 2 corrige el trayecto de ida y vuelta del pulso ultrasónico) y, si la distancia es ≤ 5 cm (umbral de demostración; en producción se recomienda 50–100 cm), invoca la rutina `allow_pedestrians()` para gestionar la secuencia de cambio de fases.
- **Comunicación**: Puerto serial UART a 9600 baud (mediante `Serial.begin(9600)` y `Serial.println()`) utilizado para depuración en tiempo real de las lecturas del sensor ultrasónico. No se implementan protocolos de red ni comunicación con sistemas externos.

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

## Diferencias entre los 3 tipos de semaforo

TODO: tabla comparativa de los 3 tipos de semaforo.

Van a haber 3 niveles de puntos, segun colores:
- 🔴 Rojo: es malo.
- 🟡 Amarillo: es regular.
- 🟢 Verde: es bueno.

| **Función / Atributo** | **Semáforo tiempo fijo** | **Semáforo con pulsador** | **Semáforo inteligente con sensores** |
| --- | --- | --- | --- |
| **Objetivo principal** | Coordinar flujo vehicular | Permitir cruce peatonal bajo demanda | Optimizar tráfico en tiempo real |
| **Adaptabilidad a variaciones** | 🔴 Baja | 🟡 Media | 🟢 Alta |
| **Respuesta a picos de demanda** | 🔴 Mala | 🟡 Regular | 🟢 Buena |
| **Necesidad de detección** | N/A | 🟡 Manual (botón) | 🟢 Automática (sensores) |
| **Complejidad de instalación** | 🟢 Baja | 🟡 Media | 🔴 Alta |
| **Costo inicial** | 🟢 Bajo | 🟡 Medio | 🔴 Alto |
| **Costo de operación y mantenimiento** | 🟢 Bajo | 🟡 Medio | 🔴 Alto |
| **Facilidad de programación** | 🟢 Fácil | 🟡 Media (interrupciones) | 🔴 Compleja |
| **Coordinación entre intersecciones** | 🟢 Buena | 🟡 Limitada | 🟢 Alta |
| **Impacto en demora promedio** | 🟡 Puede ser alto si mal dimensionado | 🟡 Moderado | 🟢 Bajo |
| **Seguridad (colisiones en ángulo)** | 🟡 Buena si fases bien diseñadas | 🟢 Alta para peatones | 🟢 Muy alta |
| **Consumo energético** | 🟢 Bajo | 🟡 Medio | 🔴 Alto |
| **Mejor caso de uso** | Corredores con demanda estable | Cruces peatonales ocasionales | Intersecciones urbanas complejas |
| **Limitaciones clave** | 🔴 Rigidez ante cambios | 🟡 Dependencia del usuario | 🔴 Complejidad y costo |

---

## Referencias

> **Aclaración sobre el uso de la Inteligencia Artificial:**
> Para la estructuración, corrección de estilo y formato Markdown de este documento, se utilizó como asistencia un asistente de desarrollo con Inteligencia Artificial y una sesión de agente de GitHub Copilot, específicamente para la descripción de la arquitectura de los semáforos.

[1] K. Behrens, "Do Crosswalk Buttons Actually Work?," Pelco, 15-mar-2026. [En línea]. Disponible: https://www.pelcoinc.com/blog/do-crosswalk-buttons-actually-work. [Accedido: 21-mar-2026].

[2] Ministerio de Obras Públicas y Transportes (MOPT), "Semáforos". [Online]. Available: https://repositorio.mopt.go.cr/server/api/core/bitstreams/90d07687-b340-4304-945b-acb89ec9cf78/content.

[3] Yangzhou FAMA Intelligent Equipment Co., Ltd. (2024). Cómo los semáforos integrados con detección de peatones mejoran la eficiencia del tráfico en las intersecciones y reducen las infracciones de luz roja. FAMA Traffic. Disponible: https://es.fama-tech.com/industry/how-pedestrian-detection-integrated-traffic-lights-improve-intersection-traffic-efficiency-and-reduce-red-light-violations.html

[4] Arduino Project Hub. "Use a buzzer module / piezo speaker using Arduino UNO." Disponible en: https://projecthub.arduino.cc/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-cf4191

[5] Arduino Project Hub. "Ultrasonic sensor with Arduino - complete guide." Disponible en: https://projecthub.arduino.cc/lucasfernando/ultrasonic-sensor-with-arduino-complete-guide-284faf

[6] arashjafari/audio-to-arduino. Disponible en: https://github.com/arashjafari/audio-to-arduino

[7] S. Cadavid Agudelo, “Criterios para justificar semáforos de tiempo fijo,” M.Sc. thesis, Escuela de Ingeniería Civil, Facultad de Minas, Universidad Nacional de Colombia, Medellín, Colombia, 2016. [En línea]. Disponible: https://bffrepositorio.unal.edu.co/server/api/core/bitstreams/3e7a306a-17c3-47db-9806-9525e2123f52/content

[8] Federal Highway Administration (FHWA), "Traffic Signal Timing Manual", 2008. Disponible en: https://ops.fhwa.dot.gov/publications/fhwahop08024/
