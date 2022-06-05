# **PROJECT: MESS JUMP** 
 *Sinh viên: BÙI ĐỨC ANH*
 
 *Lớp: K66-CC*

## 1. Hướng dẫn cài đặt (Được thực hiện dành cho Macbook M1):
   - Cài đặt SDL2 config theo như video sau: [Click Here](https://www.youtube.com/watch?v=GROeu4fL730&t=241s)
   - Tiến hành download hoặc clone source code trên github về máy
   - Dùng lệnh "make" trong terminal để tạo file chạy chương trình (thường là a.out)
   - Dùng lệnh "./a.out" để run game

## 2. Mô tả chung:
  Game được viết bằng ngôn ngữ C++ và thư viện SDL2, được lấy cảm hứng từ tựa game Mario huyền thoại
  ![image](https://user-images.githubusercontent.com/90144218/172061280-3840a259-c90e-4c9b-ab6c-37fa62baa3ed.png)

  *Cách chơi:* 
  - Người chơi điều khiển nhân vật vượt qua các chướng ngại vật trên đường đi:
     - Nhấn mũi tên trái, phải để di chuyển nhân vật qua trái hoặc phải
     - Chuột phải dùng để nhảy
  - Nếu không vượt qua được người chơi sẽ mất đi một sinh mệnh. Ngoài ra nếu va chạm với threat ở trên đường đi thì cũng mất đi 1 sinh mệnh.

       Nếu hết số sinh mệnh cho phép thì game kết thúc.
  - Số điểm được tính theo thời gian và số xu mà nhân vật kiếm được trong màn chơi.

## 3. Các chức năng chính:
  **Demo game video:** Updating...
  - Menu game cơ bản.
  - Tương tác game thông qua chuột, bàn phím: điều khiển nhân vật di chuyển qua lại, nhảy,..
  - Hệ thống hình ảnh sinh động: Background game, map game, nhân vật game, threat, ...
  - Hệ thống âm thanh bao gồm:
    - Nhạc nền (BGM)
    - Nhạc hiệu ứng(SFX): Nổ.

## 4. Các kỹ thuật lập trình được sử dụng:
 - Sử dụng thư viện lập trình SDL2 phục vụ cho đồ hoạ, tương tác game 
 - Mảng, vòng lặp game
 - Con trỏ, giải phóng bộ nhớ
 - Áp dụng kiến thức về class, struct trong lập trình hướng đối tượng: quản lý toạ độ, tính năng của đối tượng game
 - Xử lý nhảy/ rơi theo vật lý, va chạm giữa các đối tượng trong game
 - Bắt sự kiện bàn phím, chuột
 - Phân chia file quản lý từng đối tượng 
 - Đọc, ghi file

## 5. Kết luận
 **Hướng phát triển**: 
Em sẽ cải tiến thêm các tuỳ chọn bao gồm
 - Xây dựng map đa dạng, phức tạp hơn. 
 - Bổ sung thêm menu game nhằm nâng cao trải nghiệm.
 - Bổ sung các chướng ngại vật, level game.

Thông qua việc làm game cơ bản, em đã nâng cao được nhiều kĩ năng về lập trình: tìm kiếm thông tin, tư duy giải quyết vấn đề, trao đổi, học hỏi từ các tiền bối. 

Dự án này là nền tảng để em nghiên cứu sâu thêm về cách thức hoạt động, cách xây dựng các hệ thống phức tạp hơn trong tương lai.

## 6. Credit
- Nguồn tham khảo chính: [Phát Triển Phần Mềm 123A-Z](https://www.youtube.com/c/Ph%C3%A1tTri%E1%BB%83nPh%E1%BA%A7nM%E1%BB%81m123AZ)
- Hình ảnh đồ hoạ game được lấy chủ yếu từ: [Shutterstock](https://www.shutterstock.com/vi), [Freepik](https://www.freepik.com/popular)

Em chân thành cảm ơn sự giúp đỡ, hỗ trợ từ thầy Trần Quốc Long, thầy Nguyễn Việt Anh và thầy Nguyễn Văn Phi trong dự án lần này.

