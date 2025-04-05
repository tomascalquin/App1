#ifndef VENTAS_H
#define VENTAS_H

#define MAX_LINE 1024
#define MAX_ORDERS 10000
#define MAX_STRING 256
#define NUM_METRICAS 11

typedef struct {
    int pizza_id;
    int order_id;
    char pizza_name_id[MAX_STRING];
    int quantity;
    char order_date[MAX_STRING];
    char order_time[MAX_STRING];
    float unit_price;
    float total_price;
    char pizza_size[MAX_STRING];
    char pizza_category[MAX_STRING];
    char pizza_ingredients[MAX_STRING];
    char pizza_name[MAX_STRING];
} Order;

// Prototipos de funciones
void contar_ingredientes(const char *ingredientes, int *contador);
char* pizza_mas_vendida(int size, Order *orders);
char* pizza_menos_vendida(int size, Order *orders);
char* fecha_mas_ventas_dinero(int size, Order *orders);
char* fecha_menos_ventas_dinero(int size, Order *orders);
char* fecha_mas_ventas_pizzas(int size, Order *orders);
char* fecha_menos_ventas_pizzas(int size, Order *orders);
char* promedio_pizzas_por_orden(int size, Order *orders);
char* promedio_pizzas_por_dia(int size, Order *orders);
char* ingrediente_mas_vendido(int size, Order *orders);
char* cantidad_pizzas_por_categoria(int size, Order *orders);
Order* cargar_datos(int *size);
void generar_reporte(Order *orders, int size);

#endif // VENTAS_H
