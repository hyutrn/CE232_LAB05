#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "sdkconfig.h"
#include "esp_log.h"
#include "mqtt_client.h"
#include "dht11.h"
#include "oled1306.h"

static const char *TAG = "MQTT_DHT";
esp_mqtt_client_handle_t client; // Biến toàn cục để lưu trữ client MQTT

#define SECRET_MQTT_ADDRESS_URL "mqtt://mqtt3.thingspeak.com"
#define SECRET_MQTT_USERNAME "Kh09KhczPSwyBgU3KhMzDyM"
#define SECRET_MQTT_CLIENT_ID "Kh09KhczPSwyBgU3KhMzDyM"
#define SECRET_MQTT_PASSWORD "4PpuUC9tYmX/P7RpJcXYa+1T"
#define MQTT_PUBLISH_TOPIC "channels/2188986/publish/fields/field1"
#define MQTT_SUBSCRIBE_TOPIC "channels/2188986/subscribe/fields/field"
#define SECRET_MQTT_QoS 0

static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    //int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}
static void mqtt_app_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = SECRET_MQTT_ADDRESS_URL,
        .broker.address.hostname = SECRET_MQTT_ADDRESS_URL,
        .broker.address.port = 1883,
        .credentials.username = SECRET_MQTT_USERNAME,
        .credentials.client_id = SECRET_MQTT_CLIENT_ID,
        .credentials.authentication.password = SECRET_MQTT_PASSWORD,
        .session.last_will.qos = SECRET_MQTT_QoS,
    };

    client = esp_mqtt_client_init(&mqtt_cfg); // Gán giá trị cho biến client
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}

void app_main(void)
{
    DHT11_init(GPIO_NUM_4);
    oled_init();    //khoi tao oled
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("mqtt_client", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_BASE", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("outbox", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());

    mqtt_app_start();
    while (1) {
        if (client != NULL) { // Kiểm tra client đã khởi tạo hay chưa
            int temp = DHT11_read().temperature;
            //gui du lieu len broker
            char payload[32];
            sprintf(payload, "%d",temp);
            //Hien thi oled
            char text[20] = "";
            sprintf(text, "Nhiet do la: %d", temp);
            oled(text);
            printf("Temperature is %d \n", temp);
            esp_mqtt_client_publish(client, MQTT_PUBLISH_TOPIC, payload, 0, 0, 0);
            ESP_LOGI(TAG, "MQTT DATA SENT SUCCESSFULL");
        }
        vTaskDelay(10000 / portTICK_PERIOD_MS);  // Delay 10s
    }
}
