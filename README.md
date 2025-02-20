# Employee Management CLI

## Overview
The **Employee Management CLI** is a command-line tool for managing employees,
supporting various operations such as adding, listing, viewing, editing, and deleting employee records.
It also includes an HTTP mode for running as a server and a test mode for running test cases.

## Usage
```
emp [OPTIONS]
```

## Modes
The CLI operates in different modes, specified using the `-m` or `--mode` option:

| Mode    | Description |
|---------|-------------|
| `add`   | Add a new employee |
| `list`  | List all employees |
| `view`  | View details of a specific employee |
| `edit`  | Edit an existing employee |
| `delete` | Delete an employee |
| `http`  | Start the application in HTTP mode |
| `test`  | Run tests |

## Options
| Option | Short | Long | Description | Default |
|--------|-------|------|-------------|---------|
| `mode` | `-m`  | `--mode` | Specify mode (add, list, view, edit, delete, http, test) | `http` |
| `host` | `-H`  | `--host` | Specify host and port (for HTTP mode) | `localhost:5000` |
| `id`   | `-i`  | `--id` | Specify employee ID | `""` |
| `name` | `-n`  | `--name` | Specify employee name | `""` |
| `phone` | `-p`  | `--phone-number` | Specify employee phone number | `""` |
| `position` | `-P`  | `--position` | Specify employee position | `""` |
| `email` | `-e`  | `--email-address` | Specify employee email address | `""` |
| `sort-by` | `-s`  | `--sort-by` | Sort employee list by field (id, name, or phone number) | `id` |

## Examples

### Add an Employee
```
./emp --method=add --name="John Doe" --phone-number="123-456-7890" --position="Engineer" --email-address="john.doe@example.com"
```

### List Employees (Sorted by Name)
```
./emp --method=list --sort-by=name
```

### View Employee by ID
```
./emp --method=view --id="123"
```

### Edit an Employee
```
./emp --mode=edit --id="123" --position="Sr Engineer"
```

### Delete an Employee
```
./emp --mode=delete --id="123"
```

### Start HTTP Server
```
./emp --mode=http --host="localhost:5000"
```

### Run Tests
```
./emp --mode=test
```


## HTTP Endpoints

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


