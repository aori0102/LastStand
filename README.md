# 🧟‍♂️Last Stand

## 🙋‍♂️ Thông tin sinh viên

Tên sinh viên: Nguyễn Thành Dương

Mã sinh viên: 24021441

## 📄 Giới thiệu

Last stand là một tựa game bắn súng góc nhìn từ trên xuống nơi người chơi sống sót qua các đợt tấn công liên tục từ zombie.

Ngưỡng điểm mong muốn : 10!

---
## 🏆 Tại sao Game này lại xứng đáng 10/10?

### 1. 👨‍💻 Các tính năng cốt lõi (Core Mechanism):

- Hệ thống di chuyển, tương tác linh hoạt
  - Các user input được xử lí một cách hiệu quả, được lưu dưới dạng ActionState với 3 trạng thái bắt đầu (started), nhấn giữ (performed), kết thúc (cancelled) 

- Entity Component System (ECS)
  - Đây là một hệ thống được lấy cảm hứng từ Unity (một engine game mạnh và nổi tiếng)
  - Thay vì sử dụng các cấu trúc OOP cơ bản, ECS hoạt động dựa trên các GameObject, và các 'Components' giúp nhà phát triển có thể linh hoạt
    dựng mỗi GameObject theo ý muốn.
  - Mỗi Component đều có một đặc tính, chức năng riêng (Transform phụ trách di chuyển, BoxCollider phụ trách va chạm vật lí...), và được thêm vào
    các GameObject một cách dễ dàng.
  - ECS giúp việc tạo nên một GameObject không bị phụ thuộc vào sự kế thừa như OOP đối với các GameObject có nhiều thuộc tính, biểu hiện giống nhau
 
- Quản lý vật lý (Physics Manager)
  - Thay vì phương thức AABB (Axis-Aligned Bounding Box) thông thường, Physics Manager xử lí va chạm bằng cách xử dụng một số công thức toán học
    để tính toán và duyệt trên quãng đường của vật thể.
  - Khi sử dụng AABB, nếu vật thể có tốc độ quá cao, các vật thể có thể đi xuyên qua nhau (glitch), cách thức xử lí va chạm trên hoàn toàn loại bỏ
    khả năng này.
  - Ngoài ra, Physics Manager còn xử lí các tác dụng của lực (các vật thể đẩy nhau khi va chạm)
 
- Các hệ thống media, animation
  - Hệ thống media giúp cho việc thêm, bớt các media (ảnh, âm thanh, font chữ) một cách dễ dạng.
  - Hệ thống animation giúp lập trình viên dễ dàng tạo animation, liên kết các animation với nhau với các điều kiện chuyển cảnh để dễ dàng dựng lên
    các mạng lưới animation phức tạp

- Settings và lưu trữ dữ liệu
  - Settings bao gồm việc tùy chỉnh âm thanh và các nút bấm.
  - Dữ liệu của người chơi (cả settings và các thông số của người chơi) đều được lưu trữ trong %appdata%, giúp cho các file lữu trữ không bị
    mất khi lưu trong thư mục game.

### 2. 🎮 Các tính năng của trò chơi (Gameplay Features):

- Zombie và các đợt sóng
  - Có 3 loại Zombie, mỗi loại có một tính chất riêng biệt (chạy nhanh hơn, nhiều HP hơn...)
  - Mỗi đợt sóng sẽ sinh ra số lượng Zombie tăng dần và ngẫu nhiên, đảm bảo độ khó luôn tăng và mỗi màn chơi đều mới.

- Vũ khí và vật phẩm
  - Có nhiều loại vũ khí (súng lục, shotgun, súng trường) và nhiều vật phẩm (các loại đạn và bộ hồi máu)
  - Mỗi loại vũ khí đều có các tính chất, tính năng khác nhau (súng trường bắn nhanh, shotgun bắn nhiều viên đạn một lúc)
  - Hệ thống nạp đạn linh hoạt, người chơi còn có thể ngắm bắn để bắn chính xác hơn, nhưng sẽ di chuyển chậm hơn.

- Tiền và EXP
  - Người chơi sẽ được thưởng tiền và EXP (kinh nghiệm) sau mỗi lần giết Zombie, cùng với tiền thưởng thêm sau khi hoàn thành một đợt sóng.
  - Người chơi có thể dùng tiền để mua vũ khí và vật phẩm trong Shop cũng như nâng cấp vũ khí hiện có của mình.
  - Khi người chơi có đủ EXP, người chơi sẽ lên cấp (level up). Mỗi lần lên cấp sẽ được thưởng điểm kỹ năng. Người chơi có thể sử dụng điểm kỹ năng
    để nâng cấp các kỹ năng của bản thân trong Shop, giúp cho việc vượt qua các đợt tấn công dễ dàng hơn.

  
### 3. 🎨 Giao diện và trải nghiệm người dùng (UI-UX):

- Giao diện đầy đủ
 - Các giao diện được thiết kế cẩn thận, đầy đủ, dễ sử dụng.
 - Có menu, màn hình dừng game, màn hình tùy chọn (setttings)
 - Giao diện người chơi như thanh trạng thái, tiền, cấp cùng với các giao diện game như hiện thông tin của đợt Zombie.
 - Các nút bấm thay đổi linh hoạt khi di chuột, nhấp chuột.

- Âm thanh
  - Toàn bộ âm thanh trong game được lựa chọn và sửa cẩn thận, giúp có được chất lượng âm tốt nhất.
  - Khi người chơi di chuyển, zombie bị bắn, súng bắn ra... đều có âm thanh, giúp game không bị nhàm chán.
  - Còn có âm thanh khi tương tác với các nút bấm.

### 4. ⚡ Quản lí tài nguyên Game:

- Quản lí media
  - Các media (âm thanh, hình ảnh, font chữ) được quản lí bới MediaManager.
  - Các media được load sẵn, GameObject chỉ việc gọi dùng giúp tối ưu hóa việc sử dụng tài nguyên game.

- Dọn dẹp
  - Khi một GameObject bị xóa, toàn bộ thông tin của GameObject được giải phóng hoàn toàn cùng với các Component của GameObject đó.
  - MediaManager, AnimationManager... tự động dọn dẹp toàn bộ mọi thứ khi trò chơi kết thúc.

### 5. 📚 Chất lượng code:

- Tuân thủ các quy tắc cơ bản của clean code (phong cách đặt tên biến, tên hàm, tên hằng...)
- Chia file rõ ràng, không bao gồm nhiều thành phần riêng biệt cùng một file.
- Sử dụng CMake để build dự án thay vì can thiệp vào môi trường máy, điều này giúp dự án có thể được clone một cách dễ dàng
  mà không phải phụ thuộc vào môi trường máy của từng người.
- CMake còn giúp liên kết các folder với nhau, giúp cho việc chia file rõ ràng hơn.
- Dễ dàng mở rộng, thêm, bớt các tính năng bởi hầu hết đều hoạt động bằng GameObject.

## ⭐ Tóm tắt các điểm nổi bật:

- Game đã hoàn thiện tất cả các yêu cầu cơ bản và nâng cao cho một game Survival Shooter.
- Cấu trúc game được xây dựng cẩn thận, liên kết chặt chẽ với nhau, gần với mức độ của một engine.
- Các ảnh được vẽ hoàn toàn bằng tay, giúp hoạt động trơn tru và tạo thêm tính riêng cho game.
- UI được xây dựng đầy đủ và tương tác mượt mà.
- Quản lý, sử dụng tài nguyên hợp lý.

## ✅ Checklist

1. [x] Dùng các lệnh vẽ hình
2. [x] Texture
3. [x] Background
4. [x] Event bàn phím
5. [x] Event chuột
6. [x] Animation (hoạt hình)
7. [x] Xử lý va chạm
8. [x] Score (có tính điểm)
9. [x] Lưu bảng điểm
10. [x] Sound
11. [x] Sound on off
12. [x] Background music
13. [x] Font
14. [x] Menu
15. [x] Pause/Resume
16. [x] Status bar / lives (mạng/máu...)

## 📑 Tham khảo và nguồn:

## 🤖 Sử dụng AI:

- AI được sử dụng để tham khảo một số ý kiến và tra cứu một số hàm thuộc thư viện SDL (không bao gồm copy code), và một số thông tin về môi trường Windows (dùng để làm hệ
  thống lưu trữ)

## 🖼️🔊 Media (Ảnh, UI, âm thanh)

- UI được thiết kế bằng Figma
- Các sprite trong game được vẽ bằng phần mềm Aseprite
- Một số âm thanh được cắt chỉnh trước khi đưa vào sản phẩm (thông qua Audacity và Adobe Audition)

## 🔗 Các nguồn media

### Hình ảnh

[Dự án Figma thiết kế giao diện](https://www.figma.com/design/0VbwXioXDyyf05gwKCZEYs/Figma-basics?node-id=1669-162202&t=rOPQRHmF7vg3ibWc-1)

### Âm thanh

https://pixabay.com/sound-effects/submachine-gun-79846/

https://pixabay.com/sound-effects/gun-shotwav-14566/

https://pixabay.com/sound-effects/bullet-hit-metal-84818/

https://pixabay.com/sound-effects/walk-on-grass-2-291985/

https://pixabay.com/sound-effects/walk-on-grass-3-291986/

https://pixabay.com/sound-effects/walk-on-grass-1-291984/

https://pixabay.com/sound-effects/zombie-choking-44937/

https://pixabay.com/sound-effects/free-zombie-moan-sounds-54824/

https://pixabay.com/sound-effects/zombie-04-17457/

https://pixabay.com/sound-effects/coin-drop-on-grass-20269/

https://pixabay.com/sound-effects/wrong-47985/

https://pixabay.com/sound-effects/40-pistol-various-foley-23163/
