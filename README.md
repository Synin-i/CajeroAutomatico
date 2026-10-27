<div align="center">

# 🏧 Cajero Automático

### Desarrollo de un Simulador de Cajero Automático en C++

<p align="center">
  <img src="https://github.com/Synin-i/CajeroAutomatico/blob/main/Isologo%20(1).png?raw=true">
</p>

![C++](https://img.shields.io/badge/C%2B%2B-Programaci%C3%B3n-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-IDE-5C2D91?style=for-the-badge&logo=visualstudio&logoColor=white)
![VS Code](https://img.shields.io/badge/VS%20Code-Editor-007ACC?style=for-the-badge&logo=visualstudiocode&logoColor=white)
![GitHub](https://img.shields.io/badge/GitHub-Repository-181717?style=for-the-badge&logo=github)
![CSV](https://img.shields.io/badge/Data-CSV-success?style=for-the-badge)

---

## DATOS DEL PROYECTO

| Campo | Información |
| ------------- |:-------------:|
| Universidad | Universidad Privada Domingo Savio – Sub Sede La Paz |
| Asignatura | Programación III |
| Docente | Ph. D. Luigi Antequera Tamari |
| Fecha | 28/10/2026 |
| Estudiantes | Saul Jaime Aruquipa Arias |
| | Carlos Ignacio Bravo Roca |
| | Jennifer Alexa Lezama Gonzalez |
| | Limberth Alfredo Ilaluque Diaz |
| Tecnologías | C++ |

</div>

---

## Índice

- [1. Resumen](#1-resumen)
  - [1.1 Descripción del Proyecto](#11-descripción-del-proyecto)
  - [1.2 Objetivo Principal](#12-objetivo-principal)
  - [1.3 Tecnologías Utilizadas](#13-tecnologías-utilizadas)
  - [1.4 Resultados Esperados](#14-resultados-esperados)
- [2. Introducción](#2-introducción)
  - [2.1 Antecedentes](#21-antecedentes)
  - [2.2 Planteamiento del Problema](#22-planteamiento-del-problema)
  - [2.3 Objetivos](#23-objetivos)
  - [2.4 Justificación](#24-justificación)
- [3. Análisis del Problema y Requerimientos](#3-análisis-del-problema-y-requerimientos)
  - [3.1 Usuarios Objetivo](#31-usuarios-objetivo)
  - [3.2 Requerimientos Funcionales](#32-requerimientos-funcionales)
  - [3.3 Requerimientos No Funcionales](#33-requerimientos-no-funcionales)
  - [3.4 Casos de Uso](#34-casos-de-uso)
- [4. Diseño del Sistema](#4-diseño-del-sistema)
  - [4.1 Arquitectura del Software](#41-arquitectura-del-software)
  - [4.2 Diagrama de Clases y Relaciones](#42-diagrama-de-clases-y-relaciones)
  - [4.3 Modelo de Datos (MER y DER)](#43-modelo-de-datos-mer-y-der)
  - [4.4 Interfaces de Usuario](#44-interfaces-de-usuario)
- [5. Desarrollo e Implementación](#5-desarrollo-e-implementación)
  - [5.1 Lenguajes y Herramientas](#51-lenguajes-y-herramientas)
  - [5.2 Metodología de Desarrollo](#52-metodología-de-desarrollo)
  - [5.3 Estructura del Proyecto](#53-estructura-del-proyecto)
  - [5.4 Dificultades y Soluciones](#54-dificultades-y-soluciones)
- [6. Pruebas y Validación](#6-pruebas-y-validación)
  - [6.1 Casos de Prueba y Resultados](#61-casos-de-prueba-y-resultados)
  - [6.2 Errores Detectados y Correcciones](#62-errores-detectados-y-correcciones)
  - [6.3 Evaluación de Desempeño](#63-evaluación-de-desempeño)
- [7. Resultados y Conclusiones](#7-resultados-y-conclusiones)
  - [7.1 Cumplimiento de los Objetivos](#71-cumplimiento-de-los-objetivos)
  - [7.2 Impacto del Software](#72-impacto-del-software)
  - [7.3 Lecciones Aprendidas](#73-lecciones-aprendidas)
  - [7.4 Posibles Mejoras](#74-posibles-mejoras)
- [8. Manual de Usuario](#8-manual-de-usuario)
- [9. Estructura de los Archivos CSV](#9-estructura-de-los-archivos-csv)
- [10. Bibliografía](#10-bibliografía)

---

# 1. Resumen

## 1.1 Descripción del Proyecto

El presente proyecto consiste en el desarrollo de un simulador de cajero automático bancario en C++, que permite consultar saldos, realizar depósitos, retiros, transferencias entre cuentas propias y de terceros, así como pagar servicios. El sistema administra múltiples cuentas por cliente en bolivianos (BOB) y dólares estadounidenses (USD), incorporando un tipo de cambio variable para las conversiones de moneda.

## 1.2 Objetivo Principal

Desarrollar un simulador de cajero automático bancario en C++ que permita realizar operaciones financieras en bolivianos y dólares estadounidenses, incluyendo consultas de saldo, depósitos, retiros, transferencias y pagos de servicios, aplicando principios de programación estructurada y orientada a objetos.

## 1.3 Tecnologías Utilizadas

El sistema fue desarrollado en C++, utilizando clases, objetos, encapsulamiento, constructores, vectores y manejo de archivos. Se emplearon archivos CSV para almacenar y actualizar la información de clientes, cuentas, servicios y transacciones, además de una interfaz de consola para interactuar con el usuario.

## 1.4 Resultados Esperados

Se espera disponer de un sistema capaz de simular operaciones bancarias, verificar las credenciales de los usuarios, controlar la disponibilidad de fondos y actualizar los registros correspondientes después de cada transacción. Además, el proyecto demuestra la aplicación práctica de los fundamentos de programación estudiados, fortaleciendo las habilidades de análisis, diseño e implementación de software.

---

# 2. Introducción

## 2.1 Antecedentes

La evolución de las tecnologías de la información ha permitido automatizar numerosos procesos dentro del sector financiero. Entre estas herramientas se encuentran los cajeros automáticos, que permiten a los usuarios acceder a servicios financieros sin acudir directamente a una ventanilla bancaria.

En Bolivia, los cajeros automáticos forman parte de los canales de atención ofrecidos por las entidades financieras. En este contexto, el desarrollo de un simulador constituye una oportunidad para comprender los procesos involucrados en la gestión de cuentas, validación de operaciones y actualización de saldos, aplicando los conocimientos adquiridos en programación.

## 2.2 Planteamiento del Problema

El funcionamiento de un cajero automático requiere administrar información de clientes, cuentas bancarias y transacciones, además de verificar que las operaciones cumplan ciertas condiciones: identificación del usuario, disponibilidad de fondos, validación de montos y correcta actualización de saldos. Estas tareas se vuelven más complejas cuando un cliente posee varias cuentas, realiza transferencias a terceros u opera entre monedas diferentes.

Se plantea entonces el desarrollo de un sistema en C++ que simule operaciones bancarias en bolivianos y dólares estadounidenses, con un tipo de cambio variable y archivos CSV para el almacenamiento de datos.

## 2.3 Objetivos

### 2.3.1 Objetivo General

Diseñar e implementar un sistema de cajero automático bancario mediante el lenguaje C++, integrando la gestión de clientes y múltiples cuentas, la autenticación de usuarios y la ejecución de operaciones financieras (transferencias entre cuentas propias y de terceros, pagos de servicios y conversiones BOB/USD con tipo de cambio variable), utilizando archivos CSV para el almacenamiento y actualización de la información.

### 2.3.2 Objetivos Específicos

- Diseñar e implementar un sistema bancario con programación orientada a objetos, utilizando clases para gestionar clientes, cuentas, servicios y transacciones, con mecanismos de autenticación y validación de datos.
- Desarrollar las funcionalidades de consulta de saldos, depósitos, retiros, transferencias y pagos de servicios, permitiendo operaciones en bolivianos y dólares mediante un tipo de cambio variable.
- Implementar el almacenamiento y actualización de la información mediante archivos CSV, realizando pruebas funcionales que verifiquen el correcto funcionamiento de las operaciones, la integridad de los registros y el manejo de errores.

## 2.4 Justificación

El proyecto surge de la necesidad de aplicar los conocimientos de Programación III en una situación práctica. La simulación de un cajero automático integra conceptos como clases, objetos, métodos, constructores, vectores, funciones y manejo de archivos.

La elección de un sistema bancario responde a la diversidad de procesos que permite representar, desde la identificación de usuarios hasta transacciones entre cuentas de distintas monedas. Además, el uso de archivos CSV facilita el almacenamiento y recuperación de información sin requerir un sistema gestor de bases de datos, permitiendo concentrar el desarrollo en la lógica del programa.

---

# 3. Análisis del Problema y Requerimientos

## 3.1 Usuarios Objetivo

El sistema está dirigido a clientes de entidades bancarias que requieren realizar operaciones financieras de manera autónoma: consultar saldos, depositar y retirar, transferir dinero y pagar servicios. Al ser un simulador académico, también está orientado a estudiantes y docentes del área de programación.

## 3.2 Requerimientos Funcionales

| Código | Requerimiento | Descripción |
|---|---|---|
| RF-01 | Autenticación de usuarios | Verificar la identidad mediante PIN, con un máximo de tres intentos. |
| RF-02 | Selección de cuentas | Mostrar las cuentas del cliente y permitir elegir con cuál operar. |
| RF-03 | Consulta de saldo | Consultar el saldo disponible de la cuenta seleccionada con su moneda. |
| RF-04 | Depósitos y retiros | Ingresar y retirar dinero, validando montos y fondos. |
| RF-05 | Transferencias bancarias | Transferir entre cuentas propias y de terceros, verificando destino y saldo. |
| RF-06 | Conversión de monedas | Operar entre BOB y USD aplicando un tipo de cambio variable. |
| RF-07 | Pago de servicios | Seleccionar servicios por categoría, consultar deudas y realizar pagos parciales o totales. |
| RF-08 | Cambio de cuenta | Cambiar a otra cuenta del mismo cliente sin reiniciar sesión. |
| RF-09 | Gestión de información | Cargar y actualizar datos de clientes, cuentas y servicios mediante CSV. |
| RF-10 | Registro de transacciones | Guardar el historial de operaciones (identificadores, montos, monedas, fecha y hora). |
| RF-11 | Cierre de sesión | Permitir finalizar la sesión y salir del sistema. |

## 3.3 Requerimientos No Funcionales

- **Seguridad:** autenticación mediante PIN con máximo de tres intentos; operaciones únicamente sobre cuentas autorizadas; verificación de fondos y validez de montos.
- **Rendimiento:** respuestas oportunas en todas las operaciones y lectura/actualización de archivos CSV sin afectar el funcionamiento general.
- **Usabilidad:** interfaz de consola sencilla con menús numerados, instrucciones claras y mensajes de confirmación o error.

## 3.4 Casos de Uso

El actor principal es el **cliente**, quien accede a sus cuentas y realiza operaciones mediante la consola.

| Código | Caso de uso | Descripción |
|---|---|---|
| CU-01 | Iniciar sesión | El cliente ingresa su PIN para acceder al sistema. |
| CU-02 | Seleccionar cuenta | El cliente elige una de sus cuentas registradas. |
| CU-03 | Consulta de saldo | Visualiza el saldo disponible y la moneda. |
| CU-04 | Cambiar de cuenta | Selecciona otra cuenta propia sin cerrar sesión. |
| CU-05 | Cerrar sesión | Finaliza la sesión y sale del sistema. |
| CU-06 | Realizar depósito | Ingresa un monto válido que se suma al saldo. |
| CU-07 | Realizar retiro | Retira un monto si dispone de fondos suficientes. |
| CU-08 | Transferir entre cuentas propias | Transfiere entre dos cuentas propias, con conversión si las monedas difieren. |
| CU-09 | Transferir a terceros | Transfiere a una cuenta de otro cliente verificando saldo y destino. |
| CU-10 | Pagar servicios | Paga un servicio con deuda pendiente, actualizando saldo y deuda. |

---

# 4. Diseño del Sistema

## 4.1 Arquitectura del Software

El sistema fue desarrollado bajo una **arquitectura monolítica de ejecución local**, combinando programación estructurada y orientada a objetos. Se organiza en tres componentes: presentación de información, procesamiento de operaciones bancarias y almacenamiento de datos. No constituye una arquitectura Cliente-Servidor ni una implementación formal del patrón MVC.

## 4.2 Diagrama de Clases y Relaciones

El sistema se estructura en cuatro clases principales:

- **Cliente:** representa la información de los usuarios.
- **CuentaBancaria:** gestiona las cuentas y sus operaciones financieras.
- **Servicios:** administra las deudas y pagos de servicios.
- **Transaccion:** registra las operaciones realizadas.

| Relación | Descripción |
|---|---|
| Cliente – CuentaBancaria | Un cliente puede tener varias cuentas bancarias. |
| Cliente – Servicios | Un cliente puede tener varios servicios asociados. |
| CuentaBancaria – Transaccion | Una cuenta puede intervenir en múltiples transacciones, como origen o destino. |
| Servicios – Transaccion | Un servicio puede estar relacionado con diferentes transacciones de pago. |

## 4.3 Modelo de Datos (MER y DER)

Aunque no se emplea un gestor de bases de datos relacional, los registros CSV se vinculan mediante identificadores. Relaciones principales:

- Cliente – CuentaBancaria (1:N)
- Cliente – Servicios (1:N)
- Cliente – Transaccion (1:N)
- CuentaBancaria – Transaccion (1:N)
- Servicios – Transaccion (1:N)

El archivo `tipoCambio.csv` es independiente: el programa consulta su valor para las conversiones y no se relaciona por clave foránea.

## 4.4 Interfaces de Usuario

La interfaz es de consola, con menús numerados. El flujo es: **autenticación con PIN → selección de cuenta → menú principal** (saldos, depósitos, retiros, transferencias, pago de servicios, cambio de cuenta y cierre de sesión).

<!-- Agrega aquí tus capturas, por ejemplo: ![Autenticación](img/pin.png) -->

---

# 5. Desarrollo e Implementación

## 5.1 Lenguajes y Herramientas

- **Lenguaje:** C++ (programación estructurada y orientada a objetos)
- **IDEs / Editores:** Microsoft Visual Studio, Visual Studio Code y Red Panda C++
- **Bibliotecas estándar:** `iostream`, `string`, `vector`, `fstream`, `sstream`, `iomanip`, `ctime` y `windows.h`
- **Persistencia:** archivos CSV
- **Control de versiones:** Git y GitHub
- **Plataforma:** consola en Windows

## 5.2 Metodología de Desarrollo

Se aplicó un **enfoque incremental**: primero se diseñaron las clases y la lectura/escritura de CSV; luego se implementaron autenticación, consulta de saldos, depósitos, retiros, transferencias y pagos de servicios, incorporando las operaciones BOB/USD; finalmente se realizaron pruebas funcionales y correcciones.

## 5.3 Estructura del Proyecto

El programa inicia en `main()`, donde se crean los vectores de clientes, cuentas y servicios; se cargan los registros desde los CSV, se verifica el PIN, se valida el tipo de cambio y se selecciona una cuenta antes de acceder al menú principal.

Archivos de datos utilizados:

```
📁 CajeroAutomatico
 ├── clientes.csv        → información de los clientes
 ├── cuentas.csv         → cuentas bancarias y saldos
 ├── servicios.csv       → servicios y deudas pendientes
 ├── tipoCambio.csv      → tipo de cambio vigente
 └── transacciones.csv   → historial de operaciones
```

## 5.4 Dificultades y Soluciones

| Dificultad | Solución |
|---|---|
| Relacionar clientes, cuentas y servicios y mantener la información actualizada | Uso de identificadores y funciones de carga/guardado en CSV |
| Transferencias entre monedas distintas | Tipo de cambio variable, validaciones y redondeo a dos decimales |
| Validación de datos y registro de transacciones | Controles de montos inválidos, fondos insuficientes y accesos incorrectos; actualización de archivos y registro de operaciones |

---

# 6. Pruebas y Validación

## 6.1 Casos de Prueba y Resultados

| Código | Caso de prueba | Resultado esperado | Resultado obtenido |
|---|---|---|---|
| CP-01 | Inicio de sesión con credenciales válidas | Permitir el acceso | ✅ Acceso permitido |
| CP-02 | Consulta de saldo | Mostrar saldo y moneda | ✅ Información correcta |
| CP-03 | Depósito de dinero | Incrementar el saldo | ✅ Saldo actualizado |
| CP-04 | Retiro con fondos suficientes | Descontar el monto | ✅ Retiro correcto |
| CP-05 | Retiro con fondos insuficientes | Rechazar sin modificar el saldo | ✅ Operación rechazada |
| CP-06 | Transferencia entre cuentas propias | Actualizar ambas cuentas | ✅ Transferencia correcta |
| CP-07 | Transferencia entre diferentes monedas | Aplicar el tipo de cambio | ✅ Conversión y transferencia realizadas |
| CP-08 | Transferencia a terceros | Enviar dinero a otro cliente | ✅ Transferencia correcta |
| CP-09 | Pago de servicios | Descontar y actualizar la deuda | ✅ Pago registrado |
| CP-10 | Almacenamiento de transacciones | Guardar en los CSV | ✅ Registros almacenados |

## 6.2 Errores Detectados y Correcciones

- Se validaron montos negativos, valores no numéricos y saldo insuficiente, mostrando mensajes de error.
- Se limitó la autenticación a tres intentos.
- Se corrigieron transferencias y pagos con conversión BOB/USD (verificación del tipo de cambio, control de saldos y redondeo a dos decimales).
- Se mejoró el manejo de CSV con comprobaciones de lectura/escritura y restauración de valores anteriores cuando una operación no puede guardarse.

## 6.3 Evaluación de Desempeño

Al ser una aplicación de consola local, no depende de Internet ni de servidores externos. El sistema mostró un funcionamiento adecuado para el volumen de información de la simulación académica, y el uso de vectores permitió organizar y acceder a los datos durante la ejecución.

---

# 7. Resultados y Conclusiones

## 7.1 Cumplimiento de los Objetivos

Se cumplió el objetivo general mediante una aplicación en C++ capaz de simular las principales operaciones financieras en BOB y USD. Se estructuró el sistema con clases (clientes, cuentas, servicios y transacciones), se implementaron autenticación, validación de montos y control de fondos, y se incorporó el manejo de archivos CSV con registro de transacciones.

## 7.2 Impacto del Software

El programa integra diferentes operaciones financieras en un solo entorno, mantiene actualizados saldos y deudas, registra las operaciones y permite conversiones de moneda. Desde el ámbito académico, demuestra la aplicación práctica de la programación estructurada y orientada a objetos en la gestión de información financiera.

## 7.3 Lecciones Aprendidas

- Importancia de organizar el código y distribuir responsabilidades entre clases.
- Necesidad de mantener la coherencia entre los datos de clientes, cuentas y servicios en los CSV.
- Valor de las pruebas funcionales y la corrección de errores para fortalecer el análisis y la resolución de problemas.

## 7.4 Posibles Mejoras

- Implementar una **interfaz gráfica** que reemplace los menús de consola.
- Migrar a un **gestor de bases de datos** como MySQL o SQLite.
- Incorporar **seguridad avanzada**: cifrado de credenciales y control de permisos.
- Agregar **historial de transacciones**, **comprobantes** y administración de cuentas más completa.

---

# 8. Manual de Usuario

### Requisitos

Computadora con **Windows**, el programa compilado y los archivos CSV en la carpeta de datos configurada.

### Menú principal

| Opción | Operación |
|:---:|---|
| 1 | Consultar saldo |
| 2 | Retirar dinero |
| 3 | Depositar dinero |
| 4 | Transferir a cuentas propias |
| 5 | Transferir a terceros |
| 6 | Pagar servicios |
| 7 | Cambiar de cuenta |
| 0 | Cerrar sesión |

### Uso del sistema

1. **Inicio de sesión:** ingresa tu PIN. Tienes un máximo de **3 intentos**; si lo superas, la aplicación finaliza.
2. **Selección de cuenta:** elige el número de la cuenta con la que deseas operar (la opción `0` sale del sistema).
3. **Consulta de saldo:** opción 1 muestra el saldo y la moneda.
4. **Retiro:** opción 2; el sistema verifica monto válido y saldo suficiente.
5. **Depósito:** opción 3; si el monto es válido, se incrementa el saldo.
6. **Transferencia entre cuentas propias:** opción 4; se aplica el tipo de cambio si las monedas son distintas.
7. **Transferencia a terceros:** opción 5; se verifica que la cuenta destino exista y pertenezca a otro cliente.
8. **Pago de servicios:** opción 6; categorías disponibles:
   1. Servicios Básicos
   2. Telefonía, Internet y TV Cable
   3. Seguros
   4. Educación
   5. Impuestos

   Los pagos se expresan en bolivianos; si usas una cuenta en dólares se aplica conversión.
9. **Cambio de cuenta:** opción 7, sin necesidad de iniciar sesión nuevamente.
10. **Cierre de sesión:** opción 0.

> ⚠️ Este programa es un **simulador académico** con información de prueba. Las operaciones no representan movimientos bancarios reales.

---

# 9. Estructura de los Archivos CSV

| Archivo | Contenido |
|---|---|
| `clientes.csv` | Información de los clientes registrados |
| `cuentas.csv` | Cuentas bancarias y sus saldos |
| `servicios.csv` | Servicios asociados a los clientes y deudas pendientes |
| `tipoCambio.csv` | Tipo de cambio de la fecha de operación |
| `transacciones.csv` | Operaciones bancarias realizadas |

<!-- Agrega aquí capturas de cada archivo si lo deseas -->

---

# 10. Bibliografía

- Autoridad de Supervisión del Sistema Financiero. (2026). *Tarifarios*. https://asfi.gob.bo/la/tarifarios
- Gitman, L. J., McDaniel, C., Shah, A. J., Reece, M., Koffel, L., Talsma, B., & Hyatt, J. C. (2018). *Introduction to business*. OpenStax. https://openstax.org/books/introduction-business/pages/1-introduction
- International Software Testing Qualifications Board. (2024). *Certified tester foundation level syllabus* (Version 4.0.1). https://istqb.org/wp-content/uploads/2024/11/ISTQB_CTFL_Syllabus_v4.0.1.pdf
- International Organization for Standardization, International Electrotechnical Commission, & Institute of Electrical and Electronics Engineers. (2018). *Systems and software engineering—Life cycle processes—Requirements engineering* (ISO/IEC/IEEE 29148:2018). https://www.iso.org/standard/72089.html
- Object Management Group. (2017). *OMG Unified Modeling Language (OMG UML)* (Version 2.5.1). https://www.omg.org/spec/UML/2.5.1
- Sommerville, I. (2016). *Software engineering* (10th ed.). Pearson.
- Stroustrup, B. (2013). *The C++ programming language* (4th ed.). Addison-Wesley Professional.

---

<div align="center">

**Universidad Privada Domingo Savio – Sub Sede La Paz · Programación III · 2026**

</div>
