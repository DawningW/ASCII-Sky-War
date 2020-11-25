# 排名服务器后端API

## 查询排名

GET /hall

### Parameters

---

| Name | Type | Description                                                  |
| ------|--- | ------------------------------------------------------------ |
| id    | int64 | Get score entry by unique ID                                 |
| name  | string | Get score entries by player name ordered by rank             |
| record | int64 | Get top ('record' + 1 - 'record' + 11) entries ordered by rank |

## Response

---

Response content type `application/json`

| Code | Description                       |
| ---- | --------------------------------- |
| 200  | returns a array of score entries. |

### Score Entries

| Name  | Type   | Description                                   |
| ----- | ------ | --------------------------------------------- |
| id    | int64  | The unique ID of a score entry                |
| name  | string | The name of player                            |
| score | int64  | The score                                     |
| time  | int64  | The submit time of a score entry (Unix epoch) |
| rank  | int64  | The rank of a score entry                     |
| total | int64  | Total of entries on server                    |

### Example

```json
[{"id":1,"name":"azhennbnb","score":702300,"time":1606033635,"rank":1,"total":22},{"id":19,"name":"androidtest","score":85800,"time":1606211951,"rank":2,"total":22},{"id":22,"name":"wc","score":65300,"time":1606228459,"rank":3,"total":22},{"id":20,"name":"Anonym","score":46700,"time":1606222915,"rank":4,"total":22},{"id":12,"name":"Anonym","score":31200,"time":1606204190,"rank":5,"total":22},{"id":14,"name":"gznb","score":30400,"time":1606205103,"rank":6,"total":22},{"id":4,"name":"backendman","score":29500,"time":1606052403,"rank":7,"total":22},{"id":13,"name":"Anonym","score":20900,"time":1606204706,"rank":8,"total":22},{"id":18,"name":"dasddddddddddddd","score":20400,"time":1606208158,"rank":9,"total":22},{"id":21,"name":"Anonym","score":18200,"time":1606227918,"rank":10,"total":22}]
```

### Errors

| Code | Description                                  |
| ---- | -------------------------------------------- |
| 200  | returns a error code with message and detail |

```json
{
    "code": 1,
    "msg": "查询数据库失败",
    "detail": "SOME SQL ERROR"
}
```



## 提交分数

POST /hall

### Body

---

content type `application/json`

| Name | Type | Description                                                  |
| ------|--- | ------------------------------------------------------------ |
| name  | string | The name of player |
| score | int64 | The score |

## Response

---

Response content type `application/json`

| Code | Description                                                  |
| ---- | ------------------------------------------------------------ |
| 200  | returns a unique ID of the score entry submitted successfully |

```json
[{"id":1}]
```

### Errors

| Code | Description                                  |
| ---- | -------------------------------------------- |
| 200  | returns a error code with message and detail |

```json
{
    "code": 6,
    "msg": "数据检验失败",
    "detail": "用户名为空"
}
{
    "code": 2,
    "msg": "插入数据库出错",
    "detail": "SOME SQL ERROR"
}
```

