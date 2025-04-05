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

void contar_ingredientes(const char *ingredientes, int *contador) {
    char buffer[MAX_STRING];
    strcpy(buffer, ingredientes);
    char *token = strtok(buffer, ",");
    while (token != NULL) {
        while (*token == ' ') token++;
        contador[token[0]]++;
        token = strtok(NULL, ",");
    }
}

char* pizza_mas_vendida(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int max_quantity = 0;
    char max_pizza[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        if (orders[i].quantity > max_quantity) {
            max_quantity = orders[i].quantity;
            strcpy(max_pizza, orders[i].pizza_name);
        }
    }
    snprintf(resultado, MAX_STRING, "%s", max_pizza);
    return resultado;
}

char* pizza_menos_vendida(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int min_quantity = INT_MAX;
    char min_pizza[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        if (orders[i].quantity < min_quantity) {
            min_quantity = orders[i].quantity;
            strcpy(min_pizza, orders[i].pizza_name);
        }
    }
    snprintf(resultado, MAX_STRING, "%s", min_pizza);
    return resultado;
}

char* fecha_mas_ventas_dinero(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    float max_total = 0;
    char best_date[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        float sum = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                sum += orders[j].total_price;
            }
        }
        if (sum > max_total) {
            max_total = sum;
            strcpy(best_date, orders[i].order_date);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%.2f)", best_date, max_total);
    return resultado;
}

char* fecha_menos_ventas_dinero(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    float min_total = FLT_MAX;
    char worst_date[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        float sum = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                sum += orders[j].total_price;
            }
        }
        if (sum < min_total) {
            min_total = sum;
            strcpy(worst_date, orders[i].order_date);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%.2f)", worst_date, min_total);
    return resultado;
}

char* fecha_mas_ventas_pizzas(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int max_pizzas = 0;
    char best_date[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        int count = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                count += orders[j].quantity;
            }
        }
        if (count > max_pizzas) {
            max_pizzas = count;
            strcpy(best_date, orders[i].order_date);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%d)", best_date, max_pizzas);
    return resultado;
}

char* fecha_menos_ventas_pizzas(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int min_pizzas = INT_MAX;
    char worst_date[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        int count = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                count += orders[j].quantity;
            }
        }
        if (count < min_pizzas) {
            min_pizzas = count;
            strcpy(worst_date, orders[i].order_date);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%d)", worst_date, min_pizzas);
    return resultado;
}

char* promedio_pizzas_por_orden(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int total_pizzas = 0;
    int unique_orders = 0;
    int used_orders[MAX_ORDERS] = {0};

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
        if (!used_orders[orders[i].order_id]) {
            used_orders[orders[i].order_id] = 1;
            unique_orders++;
        }
    }
    float avg = (unique_orders > 0) ? (float)total_pizzas / unique_orders : 0;
    snprintf(resultado, MAX_STRING, "%.2f", avg);
    return resultado;
}

char* promedio_pizzas_por_dia(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int total_pizzas = 0;
    int unique_dates = 0;
    char used_dates[MAX_ORDERS][MAX_STRING] = {0};

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
        int found = 0;
        for (int j = 0; j < unique_dates; j++) {
            if (strcmp(orders[i].order_date, used_dates[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(used_dates[unique_dates], orders[i].order_date);
            unique_dates++;
        }
    }
    float avg = (unique_dates > 0) ? (float)total_pizzas / unique_dates : 0;
    snprintf(resultado, MAX_STRING, "%.2f", avg);
    return resultado;
}

char* ingrediente_mas_vendido(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int contador[256] = {0};

    for (int i = 0; i < *size; i++) {
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

    snprintf(resultado, MAX_STRING, "%c (aparece %d veces)", max_ingredient, max_count);
    return resultado;
}

char* cantidad_pizzas_por_categoria(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int classic = 0, veggie = 0;

    for (int i = 0; i < *size; i++) {
        if (strcmp(orders[i].pizza_category, "Classic") == 0) {
            classic += orders[i].quantity;
        } else if (strcmp(orders[i].pizza_category, "Veggie") == 0) {
            veggie += orders[i].quantity;
        }
    }
    snprintf(resultado, MAX_STRING, "Classic: %d, Veggie: %d", classic, veggie);
    return resultado;
}

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

void contar_ingredientes(const char *ingredientes, int *contador) {
    char buffer[MAX_STRING];
    strcpy(buffer, ingredientes);
    char *token = strtok(buffer, ",");
    while (token != NULL) {
        while (*token == ' ') token++;
        contador[token[0]]++;
        token = strtok(NULL, ",");
    }
}

char* pizza_mas_vendida(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int max_quantity = 0;
    char max_pizza[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        if (orders[i].quantity > max_quantity) {
            max_quantity = orders[i].quantity;
            strcpy(max_pizza, orders[i].pizza_name);
        }
    }
    snprintf(resultado, MAX_STRING, "%s", max_pizza);
    return resultado;
}

char* pizza_menos_vendida(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int min_quantity = INT_MAX;
    char min_pizza[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        if (orders[i].quantity < min_quantity) {
            min_quantity = orders[i].quantity;
            strcpy(min_pizza, orders[i].pizza_name);
        }
    }
    snprintf(resultado, MAX_STRING, "%s", min_pizza);
    return resultado;
}

char* fecha_mas_ventas_dinero(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    float max_total = 0;
    char best_date[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        float sum = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                sum += orders[j].total_price;
            }
        }
        if (sum > max_total) {
            max_total = sum;
            strcpy(best_date, orders[i].order_date);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%.2f)", best_date, max_total);
    return resultado;
}

char* fecha_menos_ventas_dinero(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    float min_total = FLT_MAX;
    char worst_date[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        float sum = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                sum += orders[j].total_price;
            }
        }
        if (sum < min_total) {
            min_total = sum;
            strcpy(worst_date, orders[i].order_date);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%.2f)", worst_date, min_total);
    return resultado;
}

char* fecha_mas_ventas_pizzas(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int max_pizzas = 0;
    char best_date[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        int count = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                count += orders[j].quantity;
            }
        }
        if (count > max_pizzas) {
            max_pizzas = count;
            strcpy(best_date, orders[i].order_date);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%d)", best_date, max_pizzas);
    return resultado;
}

char* fecha_menos_ventas_pizzas(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int min_pizzas = INT_MAX;
    char worst_date[MAX_STRING] = "";

    for (int i = 0; i < *size; i++) {
        int count = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                count += orders[j].quantity;
            }
        }
        if (count < min_pizzas) {
            min_pizzas = count;
            strcpy(worst_date, orders[i].order_date);
        }
    }
    snprintf(resultado, MAX_STRING, "%s (%d)", worst_date, min_pizzas);
    return resultado;
}

char* promedio_pizzas_por_orden(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int total_pizzas = 0;
    int unique_orders = 0;
    int used_orders[MAX_ORDERS] = {0};

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
        if (!used_orders[orders[i].order_id]) {
            used_orders[orders[i].order_id] = 1;
            unique_orders++;
        }
    }
    float avg = (unique_orders > 0) ? (float)total_pizzas / unique_orders : 0;
    snprintf(resultado, MAX_STRING, "%.2f", avg);
    return resultado;
}

char* promedio_pizzas_por_dia(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int total_pizzas = 0;
    int unique_dates = 0;
    char used_dates[MAX_ORDERS][MAX_STRING] = {0};

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;
        int found = 0;
        for (int j = 0; j < unique_dates; j++) {
            if (strcmp(orders[i].order_date, used_dates[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(used_dates[unique_dates], orders[i].order_date);
            unique_dates++;
        }
    }
    float avg = (unique_dates > 0) ? (float)total_pizzas / unique_dates : 0;
    snprintf(resultado, MAX_STRING, "%.2f", avg);
    return resultado;
}

char* ingrediente_mas_vendido(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int contador[256] = {0};

    for (int i = 0; i < *size; i++) {
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

    snprintf(resultado, MAX_STRING, "%c (aparece %d veces)", max_ingredient, max_count);
    return resultado;
}

char* cantidad_pizzas_por_categoria(int *size, struct order *orders) {
    static char resultado[MAX_STRING];
    int classic = 0, veggie = 0;

    for (int i = 0; i < *size; i++) {
        if (strcmp(orders[i].pizza_category, "Classic") == 0) {
            classic += orders[i].quantity;
        } else if (strcmp(orders[i].pizza_category, "Veggie") == 0) {
            veggie += orders[i].quantity;
        }
    }
    snprintf(resultado, MAX_STRING, "Classic: %d, Veggie: %d", classic, veggie);
    return resultado;
}
