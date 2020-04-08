# IoT-Device <-> Server

Die Kommunikation zwischen IoT-Device und Server wird über Websockets realisiert.

## IoT-Device -> Server

Die Kommunikation von IoT-Device zum Server erfolgt grundsätzlich über ein JSON Objekt mit folgendem Aufbau:

```json
{
    "messageType": 0,
    "parameters": {}
}
```

| MessageType | Bedeutung          | Parameters                        |
| ----------- | ------------------ | --------------------------------- |
| 0           | PersonCountChanged | personCount: int, timeStamp: Date |
| 1           | LoginIoTDevice     | id: string                        |

Beispiel:

```json
{
    "messageType": 0,
    "parameters": {
        "personCount": 10,
        "timeStamp": "2018-07-24T23:59:59"
    }
}
```

## Server -> IoT-Device

Die Kommunikation von Server zum IoT-Device erfolgt grundsätzlich über eine festgelegte Zeichenfolge.

Mögliche Nachrichten sind:

| Nachricht     | Bedeutung                                                                                            |
| ------------- | ---------------------------------------------------------------------------------------------------- |
| REQUEST       | Vordert das senden der aktuellen Personenanzahl an.                                                  |
| LOGIN_SUCCESS | Zeigt dem IoT-Device einen erfolgreichen Login an.                                                   |
| LOGIN_INVALID | Zeigt dem IoT-Device einen misslungenen Login an. Die Verbindung wird daraufhin vom Server getrennt. |