## Perform Account
1. Login Admin account
2. Show personal information
3. Change password: admin -> Admin
4. Logout and try login again with the old password

5. Quit and login to student account
6. Show student's info

___
## Admin 
### Add
- Following the flow: Add a year -> add a semester -> add a new course
- Do once because trong thằng add year có mấy thằng kia rùi
  ```bash
    Year: 2024-2025
        - Start: 05/10/2024
        - End:   30/09/2025
        add Class:
            24CLC2
            24APCS2
        add Student:
            Chế đi pạn :)))

    Semester: 1
        - Start: 05/10/2024
        - End:   02/01/2025

    Course: 
        - Name:         Nhập môn học máy
        - ID:           CSC14005
        - Teacher:      GV C
        - Credits:      4
        - Max studs:    90
        - Room:         I42
        - Day:          WED
        - Session:      S2

        Add students to class:
            By hand: bạn nhập đại 2 3 MSSV đi
            File: NMHM
    
  ```
  
### Modify
- Mỗi tính năng đi qua 1 lần là chắc được rùi
  
```bash
    Modify Semester:
        Year: 2022-2023
        Semester: 2
            Change to:
                - Start: 06/01/2023
                - End:   06/05/2023
    
    Modify Course:
        Year: 2022-2023
        Course: Nhập môn lập trình
            Change:
                Teacher name from Van Chi Nam to Le Thanh Tung
    
    'Test cái thêm bớt học sinh trước khi xoá course nha'

    Add/Remove students:
        Add Student:
            Add: 22127465

        Remove:
            22127465
            22127275

    Remove Course:
        Year: 2022-2023
        Course: CSC10001
        'Xoá lun thg NMLT :)))'

    Update result:
        Pạn lo nha

```

### View
- Bạn view từng mục là được

### Import/Export
- Mẫu xem cái file xuất ra

___
## Student
- Show thông tin
- Show cái còn lại