from PIL import Image, ImageDraw, ImageFont

# 1. Buat kanvas transparan ukuran standar ikon Windows (256x256)
size = 256
img = Image.new('RGBA', (size, size), (255, 255, 255, 0))
draw = ImageDraw.Draw(img)

# 2. Gambar frame luar tombol (gelap / abu-abu tua)
draw.rounded_rectangle([16, 16, 240, 240], radius=32, fill=(30, 30, 30, 255), outline=(80, 80, 80, 255), width=6)

# 3. Gambar area dalam tombol (memberikan efek 3D bevel khas keyboard)
draw.rounded_rectangle([32, 32, 224, 210], radius=24, fill=(55, 55, 55, 255))

# 4. Tambahkan teks "ESC" (Menggunakan Arial Bold bawaan Windows)
try:
    font = ImageFont.truetype("arialbd.ttf", 72)
except IOError:
    font = ImageFont.load_default()

text = "ESC"
# Kalkulasi posisi tengah untuk teks
left, top, right, bottom = draw.textbbox((0, 0), text, font=font)
x = (size - (right - left)) / 2
y = (size - (bottom - top)) / 2 - 15

# Tulis teks dengan warna merah tajam
draw.text((x, y), text, font=font, fill=(255, 70, 70, 255))

# 5. Simpan langsung sebagai format .ico multi-size
img.save('app_icon.ico', format='ICO', sizes=[(256, 256), (128, 128), (64, 64), (32, 32), (16, 16)])
print("Berhasil! File 'app_icon.ico' telah dibuat di folder proyek Anda.")