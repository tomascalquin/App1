#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

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

int main() {
    int size = 0;
    Order *orders = cargar_datos(&size);

    if (orders == NULL || size == 0) {
        fprintf(stderr, "Error: No se pudieron cargar los datos\n");
        return EXIT_FAILURE;
    }

    generar_reporte(orders, size);
    free(orders);
    return EXIT_SUCCESS;
}

Order* cargar_datos(int *size) {
    Order *orders = malloc(MAX_ORDERS * sizeof(Order));
    if (orders == NULL) return NULL;

    // Datos de ejemplo
    *size = 5;
    for (int i = 0; i < *size; i++) {
        orders[i].order_id = i + 1;
        orders[i].quantity = 10 + i;
        snprintf(orders[i].pizza_name, MAX_STRING, "Pizza %c", 'A' + i);
        snprintf(orders[i].order_date, MAX_STRING, "2023-12-%02d", i + 1);
        orders[i].total_price = 12.99 * (i + 1);
        snprintf(orders[i].pizza_category, MAX_STRING, i % 2 ? "Veggie" : "Classic");
        snprintf(orders[i].pizza_ingredients, MAX_STRING, "Queso, Tomate, %s", i % 2 ? "Champiñones" : "Pepperoni");
    }
    return orders;
}
void generar_reporte(Order *orders, int size) {
    printf("\n=== REPORTE DE VENTAS ===\n");
    printf("1. Pizza más vendida: %s\n", pizza_mas_vendida(size, orders));
    printf("2. Pizza menos vendida: %s\n", pizza_menos_vendida(size, orders));
    printf("3. Mejor día en ventas: %s\n", fecha_mas_ventas_dinero(size, orders));
    printf("4. Peor día en ventas: %s\n", fecha_menos_ventas_dinero(size, orders));
    printf("5. Día con más pizzas: %s\n", fecha_mas_ventas_pizzas(size, orders));
    printf("6. Día con menos pizzas: %s\n", fecha_menos_ventas_pizzas(size, orders));
    printf("7. Promedio por orden: %s\n", promedio_pizzas_por_orden(size, orders));
    printf("8. Promedio diario: %s\n", promedio_pizzas_por_dia(size, orders));
    printf("9. Ingrediente estrella: %s\n", ingrediente_mas_vendido(size, orders));
    printf("10. Distribución por categoría: %s\n\n", cantidad_pizzas_por_categoria(size, orders));
}

void contar_ingredientes(const char *ingredientes, int *contador) {
    char buffer[MAX_STRING];
    strncpy(buffer, ingredientes, MAX_STRING);
    char *token = strtok(buffer, ",");

    while (token != NULL) {
        while (*token == ' ') token++;
        if (*token) contador[(unsigned char)*token]++;
        token = strtok(NULL, ",");
    }
}

char* pizza_mas_vendida(int size, Order *orders) {
    static char resultado[MAX_STRING];
    int max_quantity = 0;

    for (int i = 0; i < size; i++) {
        if (orders[i].quantity > max_quantity) {
            max_quantity = orders[i].quantity;
            strncpy(resultado, orders[i].pizza_name, MAX_STRING);
        }
    }
    return resultado;
}

char* pizza_menos_vendida(int size, Order *orders) {
    static char resultado[MAX_STRING];
    int min_quantity = INT_MAX;

    for (int i = 0; i < size; i++) {
        if (orders[i].quantity < min_quantity) {
            min_quantity = orders[i].quantity;
            strncpy(resultado, orders[i].pizza_name, MAX_STRING);
        }
    }
    return resultado;
}

char* fecha_mas_ventas_dinero(int size, Order *orders) {
    static char resultado[MAX_STRING];
    float max_total = 0;
    char best_date[MAX_STRING] = "";

    for (int i = 0; i < size; i++) {
        float sum = 0;
        for (int j = 0; j < size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                sum += orders[j].total_price;
            }
        }
        if (sum > max_total) {
            max_total = sum;
            strncpy(best_date, orders[i].order_date, MAX_STRING);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (USD %.2f)", best_date, max_total);
    return resultado;
}
char* fecha_menos_ventas_dinero(int size, Order *orders) {
    static char resultado[MAX_STRING];
    float min_total = FLT_MAX;
    char worst_date[MAX_STRING] = "";

    for (int i = 0; i < size; i++) {
        float sum = 0;
        for (int j = 0; j < size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                sum += orders[j].total_price;
            }
        }
        if (sum < min_total) {
            min_total = sum;
            strncpy(worst_date, orders[i].order_date, MAX_STRING);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (USD %.2f)", worst_date, min_total);
    return resultado;
}

char* fecha_mas_ventas_pizzas(int size, Order *orders) {
    static char resultado[MAX_STRING];
    int max_pizzas = 0;
    char best_date[MAX_STRING] = "";

    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                count += orders[j].quantity;
            }
        }
        if (count > max_pizzas) {
            max_pizzas = count;
            strncpy(best_date, orders[i].order_date, MAX_STRING);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%d pizzas)", best_date, max_pizzas);
    return resultado;
}

char* fecha_menos_ventas_pizzas(int size, Order *orders) {
    static char resultado[MAX_STRING];
    int min_pizzas = INT_MAX;
    char worst_date[MAX_STRING] = "";

    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                count += orders[j].quantity;
            }
        }
        if (count < min_pizzas) {
            min_pizzas = count;
            strncpy(worst_date, orders[i].order_date, MAX_STRING);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%d pizzas)", worst_date, min_pizzas);
    return resultado;
}

char* promedio_pizzas_por_orden(int size, Order *orders) {
    static char resultado[MAX_STRING];
    int total_pizzas = 0;
    int unique_orders = 0;
    int used_orders[MAX_ORDERS] = {0};

    for (int i = 0; i < size; i++) {
        total_pizzas += orders[i].quantity;
        if (!used_orders[orders[i].order_id]) {
            used_orders[orders[i].order_id] = 1;
            unique_orders++;
        }
    }
    float avg = unique_orders > 0 ? (float)total_pizzas / unique_orders : 0;
    snprintf(resultado, MAX_STRING, "%.2f pizzas/orden", avg);
    return resultado;
}

char* promedio_pizzas_por_dia(int size, Order *orders) {
    static char resultado[MAX_STRING];
    int total_pizzas = 0;
    int unique_dates = 0;
    char used_dates[MAX_ORDERS][MAX_STRING] = {0};

    for (int i = 0; i < size; i++) {
        total_pizzas += orders[i].quantity;
        int found = 0;
        for (int j = 0; j < unique_dates; j++) {
            if (strcmp(orders[i].order_date, used_dates[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strncpy(used_dates[unique_dates], orders[i].order_date, MAX_STRING);
            unique_dates++;
        }
    }
    float avg = unique_dates > 0 ? (float)total_pizzas / unique_dates : 0;
    snprintf(resultado, MAX_STRING, "%.2f pizzas/día", avg);
    return resultado;
}

char* ingrediente_mas_vendido(int size, Order *orders) {
    static char resultado[MAX_STRING];
    int contador[256] = {0};

    for (int i = 0; i < size; i++) {
        contar_ingredientes(orders[i].pizza_ingredients, contador);
    }

    int max_count = 0;
    char max_ingredient = '\0';
    for (int i = 0; i < 256; i++) {
        if (contador[i] > max_count) {
            max_count = contador[i];
            max_ingredient = (char)i;
        }
    }
    snprintf(resultado, MAX_STRING, "'%c' (%d usos)", max_ingredient, max_count);
    return resultado;
}

char* cantidad_pizzas_por_categoria(int size, Order *orders) {
    static char resultado[MAX_STRING];
    int classic = 0, veggie = 0;

    for (int i = 0; i < size; i++) {
        if (strcmp(orders[i].pizza_category, "Classic") == 0) {
            classic += orders[i].quantity;
        } else if (strcmp(orders[i].pizza_category, "Veggie") == 0) {
            veggie += orders[i].quantity;
        }
    }
    snprintf(resultado, MAX_STRING, "Clásicas: %d | Vegetarianas: %d", classic, veggie);
    return resultado;
}
