#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <windows.h> 

using namespace std;
const string VERDE = "\033[1;32m";
const string ROJO = "\033[1;31m";
const string CIAN = "\033[1;36m";
const string AMARILLO = "\033[1;33m";
const string RESET = "\033[0m";
string ruta = "E:\\DatosCA";
double tipoCambio = 0;

class Cliente {
private:
    int pkIdCliente;
    string nombre;
    string carnetIdentidad;
    int edad;
    string email;
    string direccion;
    string numTelefono;
    string pinSeguridad;
public:
    Cliente(int pkIdCliente, string nombre, string carnetIdentidad, int edad,
        string email, string direccion, string numTelefono, string pinSeguridad)
        : pkIdCliente(pkIdCliente), nombre(nombre), carnetIdentidad(carnetIdentidad),
        edad(edad), email(email), direccion(direccion),
        numTelefono(numTelefono), pinSeguridad(pinSeguridad) {
    }
    int getPkIdCliente() { return pkIdCliente; }
    string getNombre() { return nombre; }
    string getCarnetIdentidad() { return carnetIdentidad; }
    int getEdad() { return edad; }
    string getEmail() { return email; }
    string getDireccion() { return direccion; }
    string getNumTelefono() { return numTelefono; }
    string getPinSeguridad() { return pinSeguridad; }
};
class Servicios {
private:
    int pkIdServicio;
    int fkIdCliente;
    string nombreServicio;
    string categoria;
    double montoDeuda;
public:
    Servicios(int pkIdServicio, int fkIdCliente, string nombreServicio,
        string categoria, double montoDeuda)
        : pkIdServicio(pkIdServicio), fkIdCliente(fkIdCliente),
        nombreServicio(nombreServicio), categoria(categoria), montoDeuda(montoDeuda) {
    }
    int getPkIdServicio() { return pkIdServicio; }
    int getFkIdCliente() { return fkIdCliente; }
    string getNombreServicio() { return nombreServicio; }
    string getCategoria() { return categoria; }
    double getMontoDeuda() { return montoDeuda; }
    bool pagarServicio(double monto) {
        if (monto > 0 && monto <= montoDeuda + 0.001) {
            montoDeuda -= monto;
            if (montoDeuda < 0.01) montoDeuda = 0; 
            return true;
        }
        return false;
    }
};

class CuentaBancaria {
private:
    int pkIdCuenta;
    int fkIdCliente;
    string numeroCuenta;
    double saldo;
    string tipoMoneda;
public:
    CuentaBancaria(int pkIdCuenta, int fkIdCliente, string numeroCuenta,
        double saldo, string tipoMoneda)
        : pkIdCuenta(pkIdCuenta), fkIdCliente(fkIdCliente),
        numeroCuenta(numeroCuenta), saldo(saldo), tipoMoneda(tipoMoneda) {
    }
    int getPkIdCuenta() { return pkIdCuenta; }
    int getFkIdCliente() { return fkIdCliente; }
    string getNumeroCuenta() { return numeroCuenta; }
    double getSaldo() { return saldo; }
    string getTipoMoneda() { return tipoMoneda; }
    bool depositar(double monto) {
        if (monto > 0) {
            saldo += monto;
            return true;
        }
        return false;
    }
    bool retirar(double monto) {
        if (monto > 0 && monto <= saldo + 0.001) { 
            saldo -= monto;
            if (saldo < 0.01) saldo = 0;
            return true;
        }
        return false;
    }
    bool transferir(CuentaBancaria& destino, double monto) {
        if (pkIdCuenta == destino.getPkIdCuenta()) {
            cout << endl << ROJO << "❌ No puede transferir a la misma cuenta" << RESET << endl;
            return false;
        }
        if (monto <= 0 || monto > saldo + 0.001) {
            cout << endl << ROJO << "❌ Monto Inválido o Saldo Insuficiente" << RESET << endl;
            return false;
        }
        string monedaDestino = destino.getTipoMoneda();
        if ((tipoMoneda != "BOB" && tipoMoneda != "USD") ||
            (monedaDestino != "BOB" && monedaDestino != "USD")) {
            cout << endl << ROJO << "❌ Moneda Inválida" << RESET << endl;
            return false;
        }
        double montoDestino = monto;
        if (tipoMoneda != monedaDestino) {
            if (tipoCambio <= 0) {
                cout << endl << ROJO << "❌ Tipo de Cambio Inválido" << RESET << endl;
                return false;
            }
            montoDestino = (tipoMoneda == "BOB") ? (monto / tipoCambio) : (monto * tipoCambio);
        }
        if (montoDestino <= 0) {
            cout << endl << ROJO << "❌ Monto Convertido Inválido" << RESET << endl;
            return false;
        }
        if (retirar(monto)) {
            if (destino.depositar(montoDestino)) return true;
            depositar(monto);
        }
        return false;
    }

    bool pagarServicio(Servicios& servicio, double monto) {
        if (fkIdCliente != servicio.getFkIdCliente() || monto <= 0 || monto > servicio.getMontoDeuda() + 0.001) {
            return false;
        }
        double montoCuenta = monto;
        if (tipoMoneda == "USD") {
            if (tipoCambio <= 0) return false;
            montoCuenta = monto / tipoCambio;
        }
        else if (tipoMoneda != "BOB") {
            return false;
        }
        if (montoCuenta <= 0 || montoCuenta > saldo + 0.001) return false;

        if (retirar(montoCuenta)) {
            if (servicio.pagarServicio(monto)) return true;
            depositar(montoCuenta);
        }
        return false;
    }
};

class Transaccion {
private:
    int pkIdTransaccion;
    int fkIdCliente;
    int fkIdCuentaOrigen;
    int fkIdCuentaDestino;
    int fkIdServicio;
    string tipoTransaccion;
    double montoOrigen;
    string monedaOrigen;
    double montoDestino;
    string monedaDestino;
    double tipoCambioAplicado;
    string fecha;
    string hora;

    void registrarFechaHora() {
        time_t tiempo = time(nullptr);
        tm hoy{};
        localtime_s(&hoy, &tiempo);
        stringstream fechaActual, horaActual;
        fechaActual << put_time(&hoy, "%d/%m/%Y");
        horaActual << put_time(&hoy, "%H:%M:%S");
        fecha = fechaActual.str();
        hora = horaActual.str();
    }

public:
    Transaccion(int fkIdCliente, int fkIdCuentaOrigen, string tipoTransaccion, double montoOrigen, string monedaOrigen, int fkIdCuentaDestino = 0,
        int fkIdServicio = 0, double montoDestino = 0, string monedaDestino = "", double tipoCambioAplicado = 0)
        : pkIdTransaccion(0), fkIdCliente(fkIdCliente),fkIdCuentaOrigen(fkIdCuentaOrigen), 
        fkIdCuentaDestino(fkIdCuentaDestino),fkIdServicio(fkIdServicio), tipoTransaccion(tipoTransaccion),
        montoOrigen(montoOrigen), monedaOrigen(monedaOrigen),montoDestino(montoDestino), monedaDestino(monedaDestino),
        tipoCambioAplicado(tipoCambioAplicado) {
        registrarFechaHora();
    }
    bool guardarTransaccion() {
        string nombreArchivo = ruta + "\\transacciones.csv";
        ifstream lectura(nombreArchivo);
        bool archivoNuevo = !lectura.is_open();
        int siguienteId = 1;
        string linea;
        if (lectura.is_open()) {
            getline(lectura, linea);
            while (getline(lectura, linea)) {
                if (!linea.empty()) {
                    stringstream datos(linea);
                    int id;
                    if (datos >> id && id >= siguienteId) siguienteId = id + 1;
                }
            }
            lectura.close();
        }
        ofstream archivo(nombreArchivo, ios::app);
        if (!archivo.is_open()) return false;
        if (archivoNuevo) {
            archivo << "pkIdTransaccion|fkIdCliente|fkIdCuentaOrigen|fkIdCuentaDestino|"<< "fkIdServicio|tipoTransaccion|montoOrigen|monedaOrigen|"
                    << "montoDestino|monedaDestino|tipoCambioAplicado|fecha|hora" << endl;
        }
        archivo << siguienteId << "|" << fkIdCliente << "|"
            << fkIdCuentaOrigen << "|" << fkIdCuentaDestino << "|"
            << fkIdServicio << "|" << tipoTransaccion << "|"
            << fixed << setprecision(2) << montoOrigen << "|"
            << monedaOrigen << "|" << montoDestino << "|"
            << monedaDestino << "|" << tipoCambioAplicado << "|"
            << fecha << "|" << hora << endl;
        archivo.close();
        return !archivo.fail();
    }
};

void leer(string texto, int& var);
void leer(string texto, double& var);
void leer(string texto, string& var);
void cargarClientes(vector<Cliente>& clientes);
void cargarCuentas(vector<CuentaBancaria>& cuentas);
void cargarServicios(vector<Servicios>& listaServicios);
void validarTipoCambio(double& cambio);
int verificarPin(vector<Cliente>& clientes);
int seleccionarCuenta(vector<CuentaBancaria>& cuentas, int pkIdCliente, bool permitirVolver = false);
void guardarDatosFinales(vector<CuentaBancaria>& cuentas, vector<Servicios>& listaServicios);
void realizarRetiro(vector<CuentaBancaria>& cuentas, int cuentaSeleccionada, int pkIdCliente, vector<Servicios>& listaServicios);
void realizarDeposito(vector<CuentaBancaria>& cuentas, int cuentaSeleccionada, int pkIdCliente, vector<Servicios>& listaServicios);
void realizarTransferencia(vector<CuentaBancaria>& cuentas, int cuentaSeleccionada, int pkIdCliente, bool propia, vector<Servicios>& listaServicios);
void mostrarMenuPrincipal();
void menuPrincipal(vector<CuentaBancaria>& cuentas, int cuentaSeleccionada, vector<Servicios>& listaServicios, int pkIdCliente);
void mostrarMenuServicios();
void menuServicios(vector<Servicios>& listaServicios, vector<CuentaBancaria>& cuentas, int pkIdCliente, int cuentaSeleccionada);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    vector<Cliente> clientes;
    vector<CuentaBancaria> cuentas;
    vector<Servicios> listaServicios;
    cargarClientes(clientes);
    cargarCuentas(cuentas);
    cargarServicios(listaServicios);
    if (clientes.empty() || cuentas.empty()) {
        cout << ROJO << "❌ Faltan clientes o cuentas para iniciar el sistema." << RESET << endl;
        return 1;
    }
    int pkIdCliente = verificarPin(clientes);
    validarTipoCambio(tipoCambio);
    int cuentaSeleccionada = seleccionarCuenta(cuentas, pkIdCliente);
    if (cuentaSeleccionada == -1) return 0;
    menuPrincipal(cuentas, cuentaSeleccionada, listaServicios, pkIdCliente);
    return 0;
}

void leer(string texto, int& var) {
    cout << texto;
    while (!(cin >> var)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << AMARILLO << "⚠️ Ingrese un número válido: " << RESET;
    }
}
void leer(string texto, double& var) {
    cout << texto;
    while (!(cin >> var)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << AMARILLO << "⚠️ Ingrese un número válido: " << RESET;
    }
}
void leer(string texto, string& var) {
    cout << texto;
    getline(cin >> ws, var);
}

void cargarClientes(vector<Cliente>& clientes) {
    ifstream archivo(ruta + "\\clientes.csv");
    if (!archivo.is_open()) return;
    clientes.clear();
    string linea;
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream datos(linea);
        string id, nombre, carnet, edad, email, direccion, telefono, pin;
        getline(datos, id, '|'); getline(datos, nombre, '|'); getline(datos, carnet, '|');
        getline(datos, edad, '|'); getline(datos, email, '|'); getline(datos, direccion, '|');
        getline(datos, telefono, '|'); getline(datos, pin, '|');
        if (id.empty() || edad.empty()) continue;
        clientes.push_back(Cliente(stoi(id), nombre, carnet, stoi(edad), email, direccion, telefono, pin));
    }
}

void cargarCuentas(vector<CuentaBancaria>& cuentas) {
    ifstream archivo(ruta + "\\cuentas.csv");
    if (!archivo.is_open()) return;
    cuentas.clear();
    string linea;
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream datos(linea);
        string idCuenta, idCliente, numero, moneda, saldo;
        getline(datos, idCuenta, '|'); getline(datos, idCliente, '|'); getline(datos, numero, '|');
        getline(datos, moneda, '|'); getline(datos, saldo, '|');
        if (idCuenta.empty() || idCliente.empty() || saldo.empty()) continue;
        cuentas.push_back(CuentaBancaria(stoi(idCuenta), stoi(idCliente), numero, stod(saldo), moneda));
    }
}

void cargarServicios(vector<Servicios>& listaServicios) {
    ifstream archivo(ruta + "\\servicios.csv");
    if (!archivo.is_open()) return;
    listaServicios.clear();
    string linea;
    getline(archivo, linea);
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream datos(linea);
        string idServicio, idCliente, nombre, categoria, deuda;
        getline(datos, idServicio, '|'); getline(datos, idCliente, '|'); getline(datos, nombre, '|');
        getline(datos, categoria, '|'); getline(datos, deuda, '|');
        if (idServicio.empty() || idCliente.empty() || deuda.empty()) continue;
        listaServicios.push_back(Servicios(stoi(idServicio), stoi(idCliente), nombre, categoria, stod(deuda)));
    }
}

void validarTipoCambio(double& cambio) {
    ifstream archivo(ruta + "\\tipoCambio.csv");
    string linea, fecha, valor;
    time_t tiempo = time(nullptr);
    tm hoy{};
    localtime_s(&hoy, &tiempo);
    stringstream fechaActual;
    fechaActual << put_time(&hoy, "%d/%m/%Y");
    cambio = 0;
    if (archivo.is_open()) {
        getline(archivo, linea);
        if (getline(archivo, linea)) {
            stringstream datos(linea);
            getline(datos, fecha, ',');
            getline(datos, valor);
            if (fecha == fechaActual.str()) {
                stringstream numero(valor);
                numero >> cambio;
            }
        }
    }
    if (cambio <= 0) {
        cout << endl << ROJO << "❌ Tipo de cambio de hoy necesario para continuar" << RESET << endl;
        exit(0);
    }
}

int verificarPin(vector<Cliente>& clientes) {
    string carnet, pin;
    for (int intentos = 0; intentos < 3; intentos++) {
        system("cls");
        cout << VERDE << "==========================================================" << RESET << endl;
        cout << VERDE << "           🔐 SISTEMA DE ACCESO - VERIFICACIÓN 🔐          " << RESET << endl;
        cout << VERDE << "==========================================================" << RESET << endl << endl;
        string leerConColor = CIAN + "▶ Ingrese Pin: " + RESET;
        leer(leerConColor, pin);
        for (Cliente& cliente : clientes) {
            if (cliente.getPinSeguridad() == pin) {
                cout << endl << VERDE << "[ ✓ ] Acceso Permitido" << RESET << endl;
                cout << CIAN << "👋 ¡Bienvenido, " << cliente.getNombre() << "!" << RESET << endl;
                system("pause >nul");
                return cliente.getPkIdCliente();
            }
        }
        cout << endl << ROJO << "[ ✗ ] Datos Incorrectos" << RESET << endl;
        cout << AMARILLO << "⚠️ Intentos Restantes: " << 2 - intentos << RESET << endl;
        system("pause >nul");
    }
    cout << endl << ROJO << "🔒 Demasiados intentos. Cerrando el sistema..." << RESET << endl;
    exit(0);
}

int seleccionarCuenta(vector<CuentaBancaria>& cuentas, int pkIdCliente, bool permitirVolver) {
    vector<int> posiciones;
    for (size_t i = 0; i < cuentas.size(); i++) {
        if (cuentas[i].getFkIdCliente() == pkIdCliente) posiciones.push_back(i);
    }
    if (posiciones.empty()) {
        cout << AMARILLO << "⚠️ El cliente no tiene cuentas registradas" << RESET << endl;
        system("pause >nul");
        return -1;
    }
    while (true) {
        system("cls");
        cout << VERDE << "==========================================================" << RESET << endl;
        cout << VERDE << "              🏧 SELECCIONE UNA CUENTA 🏧              " << RESET << endl;
        cout << VERDE << "==========================================================" << RESET << endl << endl;
        for (size_t i = 0; i < posiciones.size(); i++) {
            CuentaBancaria& cuenta = cuentas[posiciones[i]];
            cout << "  [ " << i + 1 << " ] 💳 " << cuenta.getNumeroCuenta()
                << " - 🪙 " << cuenta.getTipoMoneda() << endl;
        }
        cout << endl << ROJO << (permitirVolver ? "  [ 0 ] Volver" : "  [ 0 ] Salir") << RESET << endl;
        cout << VERDE << "\n==========================================================" << RESET << endl << endl;
        int opcion;
        leer(CIAN + "▶ Seleccione una cuenta: " + RESET, opcion);
        if (opcion == 0) return -1;
        if (opcion >= 1 && opcion <= posiciones.size()) return posiciones[opcion - 1];
        cout << endl << ROJO << "❌ Opción Inválida" << RESET << endl;
        system("pause >nul");
    }
}
void guardarDatosFinales(vector<CuentaBancaria>& cuentas, vector<Servicios>& listaServicios) {
    ofstream archivoCuentas(ruta + "\\cuentas.csv", ios::trunc);
    if (archivoCuentas.is_open()) {
        archivoCuentas << "pkIdCuenta|fkIdCliente|numeroCuenta|tipoMoneda|saldo" << endl;
        for (CuentaBancaria& c : cuentas) {
            archivoCuentas << c.getPkIdCuenta() << "|" << c.getFkIdCliente() << "|"
                << c.getNumeroCuenta() << "|" << c.getTipoMoneda() << "|"
                << fixed << setprecision(2) << c.getSaldo() << endl;
        }
        archivoCuentas.close();
    }
    ofstream archivoServ(ruta + "\\servicios.csv", ios::trunc);
    if (archivoServ.is_open()) {
        archivoServ << "pkIdServicio|fkIdCliente|nombreServicio|categoria|montoDeuda" << endl;
        for (Servicios& s : listaServicios) {
            archivoServ << s.getPkIdServicio() << "|" << s.getFkIdCliente() << "|"
                << s.getNombreServicio() << "|" << s.getCategoria() << "|"
                << fixed << setprecision(2) << s.getMontoDeuda() << endl;
        }
        archivoServ.close();
    }
}

void realizarRetiro(vector<CuentaBancaria>& cuentas, int cuentaSeleccionada, int pkIdCliente, vector<Servicios>& listaServicios) {
    double monto;
    cout << endl << VERDE << "==================== 💵 RETIRAR DINERO ===================" << RESET << endl;
    leer(CIAN + "▶ Monto a Retirar: " + RESET, monto);

    CuentaBancaria& cuenta = cuentas[cuentaSeleccionada];

    if (cuenta.retirar(monto)) {
        Transaccion retiro(pkIdCliente, cuenta.getPkIdCuenta(), "Retiro", monto, cuenta.getTipoMoneda());
        retiro.guardarTransaccion();
        guardarDatosFinales(cuentas, listaServicios); 
        cout << endl << VERDE << "✅ Retiro Exitoso" << RESET << endl;
    }
    else {
        cout << endl << ROJO << "❌ Monto Inválido o Saldo Insuficiente" << RESET << endl;
    }
}

void realizarDeposito(vector<CuentaBancaria>& cuentas, int cuentaSeleccionada, int pkIdCliente, vector<Servicios>& listaServicios) {
    double monto;
    cout << endl << VERDE << "=================== 📥 DEPOSITAR DINERO ==================" << RESET << endl;
    leer(CIAN + "▶ Monto a Depositar: " + RESET, monto);

    CuentaBancaria& cuenta = cuentas[cuentaSeleccionada];

    if (cuenta.depositar(monto)) {
        Transaccion deposito(pkIdCliente, cuenta.getPkIdCuenta(), "Deposito", monto, cuenta.getTipoMoneda());
        deposito.guardarTransaccion();
        guardarDatosFinales(cuentas, listaServicios); 
        cout << endl << VERDE << "✅ Depósito Exitoso" << RESET << endl;
    }
    else {
        cout << endl << ROJO << "❌ Monto Inválido" << RESET << endl;
    }
}

void realizarTransferencia(vector<CuentaBancaria>& cuentas, int cuentaSeleccionada, int pkIdCliente, bool propia, vector<Servicios>& listaServicios) {
    if (propia) cout << endl << VERDE << "============= 🔄 TRANSFERIR A CUENTAS PROPIAS ============" << RESET << endl;
    else cout << endl << VERDE << "=============== 💸 TRANSFERIR A TERCEROS =================" << RESET << endl;

    string numeroDestino;
    leer(CIAN + "▶ Cuenta Destino: " + RESET, numeroDestino);

    int indiceDestino = -1;
    for (size_t i = 0; i < cuentas.size(); i++) {
        if (cuentas[i].getNumeroCuenta() == numeroDestino && cuentas[i].getPkIdCuenta() != cuentas[cuentaSeleccionada].getPkIdCuenta()) {
            bool mismoCliente = cuentas[i].getFkIdCliente() == pkIdCliente;
            if (mismoCliente == propia) indiceDestino = i;
            break;
        }
    }

    if (indiceDestino == -1) {
        cout << endl << ROJO << "❌ Cuenta Destino No Encontrada o No Permitida" << RESET << endl;
        return;
    }
    double monto = 0;
    leer(CIAN + "▶ Monto a Transferir: " + RESET, monto);
    CuentaBancaria& origen = cuentas[cuentaSeleccionada];
    CuentaBancaria& destino = cuentas[indiceDestino];
    double saldoAnterior = destino.getSaldo();
    if (origen.transferir(destino, monto)) {
        double recibido = destino.getSaldo() - saldoAnterior;
        double cambio = (origen.getTipoMoneda() != destino.getTipoMoneda()) ? tipoCambio : 0;
        string tipo = propia ? "Transferencia Propia" : "Transferencia Terceros";
        Transaccion trans(pkIdCliente, origen.getPkIdCuenta(), tipo, monto, origen.getTipoMoneda(),
            destino.getPkIdCuenta(), 0, recibido, destino.getTipoMoneda(), cambio);
        trans.guardarTransaccion();
        guardarDatosFinales(cuentas, listaServicios); 
        cout << endl << VERDE << "✅ Transferencia Exitosa" << RESET << endl;
        cout << CIAN << "📤 Monto Enviado:  " << RESET << fixed << setprecision(2) << monto << " " << origen.getTipoMoneda() << endl;
        cout << CIAN << "📥 Monto Recibido: " << RESET << fixed << setprecision(2) << recibido << " " << destino.getTipoMoneda() << endl;
    }
    else {
        cout << AMARILLO << "⚠️ Transferencia No Realizada" << RESET << endl;
    }
}

void mostrarMenuPrincipal() {
    cout << VERDE << "         🏧 CAJERO AUTOMÁTICO - MENÚ PRINCIPAL 🏧         " << RESET << endl;
    cout << VERDE << "==========================================================" << RESET << endl << endl;
    cout << "  [ 1 ] 💰 Consultar saldo" << endl;
    cout << "  [ 2 ] 💵 Retirar dinero" << endl;
    cout << "  [ 3 ] 📥 Depositar dinero" << endl;
    cout << "  [ 4 ] 🔄 Transferir a cuentas propias" << endl;
    cout << "  [ 5 ] 💸 Transferir a terceros" << endl;
    cout << "  [ 6 ] 🧾 Pagar servicios" << endl;
    cout << "  [ 7 ] 💳 Cambiar de cuenta" << endl << endl;
    cout << ROJO << "  [ 0 ] Cerrar sesión" << RESET << endl; 
    cout << VERDE << "\n==========================================================" << RESET << endl;
}

void mostrarMenuServicios() {
    cout << VERDE << "==========================================================" << RESET << endl;
    cout << VERDE << "                 🧾 PAGO DE SERVICIOS 🧾                  " << RESET << endl;
    cout << VERDE << "==========================================================" << RESET << endl << endl;
    cout << "  [ 1 ] 💧 Servicios Básicos" << endl;
    cout << "  [ 2 ] 📱 Telefonía, Internet y TV Cable" << endl;
    cout << "  [ 3 ] 🛡️ Seguros" << endl;
    cout << "  [ 4 ] 🎓 Educación" << endl;
    cout << "  [ 5 ] 🏛️ Impuestos" << endl << endl;
    cout << ROJO << "  [ 0 ] Volver al Menú Principal" << RESET << endl;
    cout << VERDE << "\n==========================================================" << RESET << endl;
}

void menuServicios(vector<Servicios>& listaServicios, vector<CuentaBancaria>& cuentas, int pkIdCliente, int cuentaSeleccionada) {
    while (true) {
        system("cls");
        mostrarMenuServicios();
        int opcionCategoria;
        leer(CIAN + "▶ Seleccione una categoría: " + RESET, opcionCategoria);
        string categoria;
        switch (opcionCategoria) {
        case 1: categoria = "Servicios Basicos"; break;
        case 2: categoria = "Telefonia, Internet y TV Cable"; break;
        case 3: categoria = "Seguros"; break;
        case 4: categoria = "Educacion"; break;
        case 5: categoria = "Impuestos"; break;
        case 0: return;
        default:
            cout << endl << ROJO << "❌ Opción Inválida" << RESET << endl;
            system("pause >nul"); continue;
        }

        vector<int> posiciones;
        for (size_t i = 0; i < listaServicios.size(); i++) {
            if (listaServicios[i].getFkIdCliente() == pkIdCliente && listaServicios[i].getCategoria() == categoria) {
                posiciones.push_back(i);
            }
        }

        while (true) {
            system("cls");
            cout << VERDE << "==========================================================" << RESET << endl;
            cout << VERDE << "                 🧾 " << categoria << " 🧾                 " << RESET << endl;
            cout << VERDE << "==========================================================" << RESET << endl << endl;

            for (size_t i = 0; i < posiciones.size(); i++) {
                cout << "  [ " << i + 1 << " ] 🏢 " << listaServicios[posiciones[i]].getNombreServicio() << endl;
            }
            if (posiciones.empty()) cout << AMARILLO << "  ⚠️ No tiene servicios en esta categoría" << RESET << endl;

            cout << endl << ROJO << "  [ 0 ] Volver a categorías" << RESET << endl;
            cout << VERDE << "\n==========================================================" << RESET << endl << endl;

            int opcionServicio;
            leer(CIAN + "▶ Seleccione un servicio: " + RESET, opcionServicio);
            if (opcionServicio == 0) break;
            if (opcionServicio < 1 || opcionServicio > posiciones.size()) {
                cout << endl << ROJO << "❌ Opción Inválida" << RESET << endl;
                system("pause >nul"); continue;
            }

            Servicios& servicio = listaServicios[posiciones[opcionServicio - 1]];

            while (true) {
                system("cls");
                cout << VERDE << "==========================================================" << RESET << endl;
                cout << VERDE << "               🏢 " << servicio.getNombreServicio() << " 🏢               " << RESET << endl;
                cout << VERDE << "==========================================================" << RESET << endl;
                cout << CIAN << "  🏷️  Categoría: " << RESET << servicio.getCategoria() << endl;
                cout << CIAN << "  💸 Deuda Pendiente: " << RESET << fixed << setprecision(2) << servicio.getMontoDeuda() << " BOB" << endl;
                cout << VERDE << "==========================================================" << RESET << endl << endl;
                cout << "  [ 1 ] 💳 Pagar Servicio" << endl << endl;
                cout << ROJO << "  [ 0 ] Volver a servicios" << RESET << endl;
                cout << VERDE << "\n==========================================================" << RESET << endl << endl;

                int opcionPago;
                leer(CIAN + "▶ Seleccione una opción: " + RESET, opcionPago);
                if (opcionPago == 0) break;
                if (opcionPago != 1) {
                    cout << endl << ROJO << "❌ Opción Inválida" << RESET << endl;
                    system("pause >nul"); continue;
                }
                if (servicio.getMontoDeuda() <= 0) {
                    cout << endl << AMARILLO << "⚠️ Este servicio no tiene deuda pendiente" << RESET << endl;
                    system("pause >nul"); continue;
                }

                double monto;
                leer(CIAN + "▶ Monto a Pagar (BOB): " + RESET, monto);

                CuentaBancaria& cuenta = cuentas[cuentaSeleccionada];
                double saldoAnterior = cuenta.getSaldo();

                if (cuenta.pagarServicio(servicio, monto)) {
                    double cobrado = saldoAnterior - cuenta.getSaldo();
                    double cambioAplicado = (cuenta.getTipoMoneda() == "USD") ? tipoCambio : 0;
                    Transaccion pago(pkIdCliente, cuenta.getPkIdCuenta(), "Pago Servicio",
                        cobrado, cuenta.getTipoMoneda(), 0,
                        servicio.getPkIdServicio(), monto, "BOB", cambioAplicado);
                    pago.guardarTransaccion();
                    guardarDatosFinales(cuentas, listaServicios); 

                    cout << endl << VERDE << "✅ Pago Exitoso" << RESET << endl;
                    cout << CIAN << "💸 Deuda Restante: " << RESET << fixed << setprecision(2) << servicio.getMontoDeuda() << " BOB" << endl;
                }
                else {
                    cout << endl << ROJO << "❌ Monto Inválido o Saldo Insuficiente" << RESET << endl;
                }
                system("pause >nul");
            }
        }
    }
}

void menuPrincipal(vector<CuentaBancaria>& cuentas, int cuentaSeleccionada, vector<Servicios>& listaServicios, int pkIdCliente) {
    int opcion;
    do {
        system("cls");
        cout << VERDE << "==========================================================" << RESET << endl;
        cout << CIAN << "  💳 Cuenta: " << RESET << cuentas[cuentaSeleccionada].getNumeroCuenta() << endl;
        cout << CIAN << "  🪙 Moneda: " << RESET << cuentas[cuentaSeleccionada].getTipoMoneda() << endl;
        mostrarMenuPrincipal();

        leer(CIAN + "▶ Seleccione una opción: " + RESET, opcion);

        switch (opcion) {
        case 1:
            cout << endl << VERDE << "----------------------------------------------------------" << RESET << endl;
            cout << CIAN << "  💰 Saldo Disponible: " << RESET << fixed << setprecision(2)
                << cuentas[cuentaSeleccionada].getSaldo() << " " << cuentas[cuentaSeleccionada].getTipoMoneda() << endl;
            cout << VERDE << "----------------------------------------------------------" << RESET << endl;
            break;
        case 2:
            realizarRetiro(cuentas, cuentaSeleccionada, pkIdCliente, listaServicios);
            break;
        case 3:
            realizarDeposito(cuentas, cuentaSeleccionada, pkIdCliente, listaServicios);
            break;
        case 4:
            realizarTransferencia(cuentas, cuentaSeleccionada, pkIdCliente, true, listaServicios);
            break;
        case 5:
            realizarTransferencia(cuentas, cuentaSeleccionada, pkIdCliente, false, listaServicios);
            break;
        case 6:
            menuServicios(listaServicios, cuentas, pkIdCliente, cuentaSeleccionada);
            break;
        case 7: {
            int nuevaCuenta = seleccionarCuenta(cuentas, pkIdCliente, true);
            if (nuevaCuenta != -1) {
                cuentaSeleccionada = nuevaCuenta;
                cout << endl << VERDE << "✅ Cuenta Cambiada Exitosamente" << RESET << endl;
            }
            break;
        }
        case 0: 
            cout << endl << CIAN << "👋 Cerrando sesión... ¡Gracias por utilizar nuestro cajero!" << RESET << endl;
            break;
        default:
            cout << endl << ROJO << "❌ Opción Inválida" << RESET << endl;
            break;
        }

        if (opcion != 0) system("pause >nul");
    } while (opcion != 0); 
}