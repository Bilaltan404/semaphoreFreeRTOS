#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

TaskHandle_t task1Handle;
TaskHandle_t task2Handle;

SemaphoreHandle_t xSemaphore = NULL;

uint32_t sharedValue = 0; // Shared variable

void task1(void *arg)
{
    while (1)
    {
        // Try to take semaphore
        if (xSemaphoreTake(xSemaphore, (TickType_t)10) == pdTRUE)
        {
            // Increment shared value
            sharedValue += 5;
            printf(" Task 1 sharedValue : %d\n", sharedValue);

            // Give semaphore back
            xSemaphoreGive(xSemaphore);
        }
        else
        {
            // Failed to take semaphore
            printf("Task 1: Failed to take semaphore!\n");
        }

        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds
    }
}

void task2(void *arg)
{
    while (1)
    {
        // Try to take semaphore
        if (xSemaphoreTake(xSemaphore, (TickType_t)10) == pdTRUE)
        {
            // Decrement shared value
            sharedValue -= 3;
            printf(" Task 2 sharedValue : %d\n", sharedValue);

            // Give semaphore back
            xSemaphoreGive(xSemaphore);
        }
        else
        {
            // Failed to take semaphore
            printf("Task 2: Failed to take semaphore!\n");
        }

        vTaskDelay(pdMS_TO_TICKS(4000)); // Delay for 4 seconds
    }
}

void app_main(void)
{
    // Create binary semaphore
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore); // Initialize semaphore

    // Create task 1
    xTaskCreate(task1, "task1", 4096, NULL, 4, &task1Handle);

    // Create task 2
    xTaskCreate(task2, "task2", 4096, NULL, 5, &task2Handle);
}
