# Employee Management API

## Endpoints

### 1. Get Employee List
**Endpoint:** `GET /api/employees`

**Query Parameters:**
| Parameter  | Type    | Default | Description                                    |
|------------|---------|---------|------------------------------------------------|
| `sort-by`  | string  | `id`    | Sort by field (`id`, `name`, `phone-number`).  |
| `asc`      | bool    | `true`  | Sort in ascending order if `true`.             |

**Response Body (JSON):**
```json
[
  {
    "id": "123",
    "name": "Sugeng",
    "phoneNumber": "123-456-7890",
    "position": "Software Engineer",
    "emailAddress": "sugeng@example.com"
  },
  {
    "id": "321",
    "name": "Slamet",
    "phoneNumber": "321-645-0987",
    "position": "Product Manager",
    "emailAddress": "slamet@example.com"
  }
]
```

### 2. Get Employee Details
**Endpoint:** `GET /api/employee`

**Query Parameters:**
| Parameter | Type   | Required | Description       |
|-----------|--------|----------|-------------------|
| `id`      | string | Yes      | Employee ID.      |

**Response Body (JSON):**
```json
{
  "id": "111",
  "name": "Asep",
  "phoneNumber": "111-222-3333",
  "position": "Senior Developer",
  "emailAddress": "Asep@example.com"
}
```

### 3. Add New Employee
**Endpoint:** `POST /employee`

**Request Body (JSON):**
```json
{
  "name": "John Doe",
  "phoneNumber": "555-666-7777",
  "position": "Software Engineer",
  "emailAddress": "johndoe@example.com"
}
```

**Response Body (JSON):**
```json
{
  "id": "456",
  "name": "John Doe",
  "phoneNumber": "555-666-7777",
  "position": "Junior Engineer",
  "emailAddress": "johndoe@example.com"
}
```

### 4. Update Employee Details
**Endpoint:** `PUT /employee`

**Request Body (JSON):**
```json
{
  "id": "456",
  "name": "John Doe",
  "phoneNumber": "555-666-7777",
  "position": "Senior Engineer",
  "emailAddress": "johndoe@example.com"
}
```

> **Note:** All fields except `id` are optional; only provided fields will be updated.

**Response:**
- **200 OK**: Employee successfully updated.
- **400 Bad Request**: Invalid request data.
- **404 Not Found**: Employee not found.
- **500 Internal Server Error**: Server error.

### 5. Delete Employee
**Endpoint:** `DELETE /employee`

**Request Body (JSON):**
```json
{
  "id": "123"
}
```

**Response:**
- **200 OK**: Employee successfully deleted.
- **400 Bad Request**: Invalid request data.
- **404 Not Found**: Employee not found.
- **500 Internal Server Error**: Server error.


