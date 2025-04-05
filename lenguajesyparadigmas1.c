#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_ORDERS 10000
#define MAX_STRING 256
#define NUM_METRICAS 11

struct order {
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
};


char* pizza_mas_vendida(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}

char* pizza_menos_vendida(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}

char* fecha_mas_ventas_dinero(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}

char* fecha_menos_ventas_dinero(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}

char* fecha_mas_ventas_pizzas(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}

char* fecha_menos_ventas_pizzas(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}

char* promedio_pizzas_por_orden(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}

char* promedio_pizzas_por_dia(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}

char* ingrediente_mas_vendido(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}

char* cantidad_pizzas_por_categoria(int *size, struct order *orders) {
    static char resultado[MAX_STRING] = "Placeholder";
    return resultado;
}
