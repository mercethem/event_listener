# File System Event Listener

A Windows file system monitoring and email notification application. Monitors file changes (create, delete, rename, modify) in real-time in your specified directory and optionally sends email notifications.

---

##  Table of Contents

- [Features](#features)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [Email Settings](#email-settings)
- [Troubleshooting](#troubleshooting)
- [Security Notes](#security-notes)
- [Contributing](#contributing)

## Features

- **Real-Time Monitoring**: Monitors directory changes instantly using Windows file system APIs
- **File Filtering**: Filter specific file extensions to monitor only the file types you want
- **Email Notifications**: Automatically sends email notifications on file changes
- **Multiple Email Provider Support**: Gmail, Outlook, Hotmail, Yandex, Yahoo, iCloud, and custom SMTP servers
- **Detailed Information**: Includes file name, full path, size, timestamp, and type information
- **Configurable**: Easy configuration via `config.ini` file

## System Requirements

### Required Software

- **Operating System**: Windows 10 or higher
- **Compiler**: MSVC (Visual Studio 2019 or higher) or compatible C++20 compiler
- **CMake**: Version 3.20 or higher
- **C++ Standard**: C++20

### Dependencies

- **libcurl**: For email sending functionality (can be installed via vcpkg)
- **zlib**: For libcurl's compression support (comes with libcurl)
- **Windows SDK**: For Windows APIs

### vcpkg Installation (Recommended)

1. Clone vcpkg:
   ```powershell
   git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
   cd C:\vcpkg
   .\bootstrap-vcpkg.bat
   ```

2. Install libcurl:
   ```powershell
   .\vcpkg install curl:x64-windows-static
   ```

3. Update the vcpkg path in CMakeLists.txt according to your installation:
   ```cmake
   set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
   ```

## Installation

### 1. Clone the Project

```bash
git clone https://github.com/username/event_listener.git
cd event_listener
```

### 2. Build with CMake

**If using CLion:**
- Open the project and CLion will automatically run CMake
- Click the Build button or press `Ctrl+F9`

**From command line:**
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### 3. Create Configuration File

The `config.ini` file is not included in the project as it's in `.gitignore`. Create your own `config.ini` file:

```ini
# Directory to monitor
DIRECTORY=C:\Users\YourName\Desktop\monitored

# Email settings
PROVIDER=Gmail
CUSTOM_SMTP_URL=

# Credentials
USERNAME=your_email@gmail.com
PASSWORD=your_app_password
RECIPIENT=recipient@example.com
```

##  Configuration

### config.ini File

The `config.ini` file is the main configuration file for the application. This file can be located in the project root directory, the executable's directory, or the current working directory.

#### File Location Priority

The application searches for `config.ini` in the following order:
1. Executable's directory
2. Executable's parent directory (project root)
3. Current working directory

If the file is not found, the application switches to interactive mode and prompts the user for settings.

#### Configuration Parameters

##### DIRECTORY
- **Description**: Directory path to monitor
- **Format**: Windows directory path (e.g., `C:\Users\YourName\Desktop\monitored`)
- **Required**: No (if left empty, user will be prompted)
- **Example**: `DIRECTORY=C:\Users\user\Desktop\monitored`

##### PROVIDER
- **Description**: Email provider
- **Values**: 
  - `Gmail` - Gmail
  - `Outlook` - Outlook (@outlook.com)
  - `Hotmail` - Hotmail (@hotmail.com, @live.com)
  - `Yandex` - Yandex Mail
  - `Yahoo` - Yahoo Mail
  - `iCloud` - Apple Mail (@me.com, @icloud.com)
  - `Custom` - Custom SMTP server
- **Required**: No (if left empty, email feature will be disabled)
- **Example**: `PROVIDER=Gmail`

##### CUSTOM_SMTP_URL
- **Description**: Custom SMTP server URL (required only if `PROVIDER=Custom`)
- **Format**: `smtp://server.com:port` (e.g., `smtp://smtp.example.com:587`)
- **Required**: Only if `PROVIDER=Custom`
- **Example**: `CUSTOM_SMTP_URL=smtp://smtp.example.com:587`

##### USERNAME
- **Description**: Your email address (for SMTP authentication)
- **Format**: Email address
- **Required**: Yes if email feature will be used
- **Example**: `USERNAME=your_email@gmail.com`

##### PASSWORD
- **Description**: Your email password or application password (App Password)
- **Note**: For Gmail, you must use an [App Password](https://support.google.com/accounts/answer/185833) instead of your regular password
- **Required**: Yes if email feature will be used
- **Example**: `PASSWORD=abcd efgh ijkl mnop`

##### RECIPIENT
- **Description**: Email address where notifications will be sent
- **Format**: Email address
- **Required**: Yes if email feature will be used
- **Example**: `RECIPIENT=recipient@example.com`

#### Comment Lines

Lines starting with `#` in the `config.ini` file are treated as comments and are not processed:

```ini
# This is a comment line
DIRECTORY=C:\Users\YourName\Desktop\monitored  # This is also a comment
```

#### Empty Values

If a parameter is left empty (e.g., `DIRECTORY=`), the application treats this value as invalid and prompts the user interactively.

## Email Settings

### Using Gmail

For Gmail, you must use an **App Password** instead of your regular password:

1. Enable 2-Step Verification in your Google Account
2. Go to [App Passwords](https://myaccount.google.com/apppasswords) page
3. Select "Mail" for "App"
4. Select "Windows Computer" for "Device"
5. Click "Generate"
6. Enter the 16-character password in the `PASSWORD` field in your `config.ini` file

**Example config.ini:**
```ini
PROVIDER=Gmail
USERNAME=your_email@gmail.com
PASSWORD=abcd efgh ijkl mnop
RECIPIENT=recipient@gmail.com
```

### Using Outlook/Hotmail

For Outlook and Hotmail, you can use your regular password:

```ini
PROVIDER=Outlook
USERNAME=your_email@outlook.com
PASSWORD=your_password
RECIPIENT=recipient@outlook.com
```

### Custom SMTP Server

To use your own SMTP server:

```ini
PROVIDER=Custom
CUSTOM_SMTP_URL=smtp://smtp.example.com:587
USERNAME=your_email@example.com
PASSWORD=your_password
RECIPIENT=recipient@example.com
```

### Disabling Email Feature

If you don't want to use email notifications, leave the `PROVIDER`, `USERNAME`, `PASSWORD`, or `RECIPIENT` fields empty or don't include them in the `config.ini` file. When the application starts, email settings will be requested, and you can skip by pressing Enter.

## Usage

### Basic Usage

1. Configure your `config.ini` file (see the section above)
2. Run the application:
   ```powershell
   .\event_listener.exe
   ```
3. If `DIRECTORY` is not specified in `config.ini`, enter the directory to monitor
4. Select file extensions to monitor (separated by commas, e.g., `txt,doc,pdf`)
5. Press Enter to stop monitoring

### File Extension Filtering

When the application starts, you will be prompted to select file extensions to monitor:

- **Specific extensions**: Enter comma-separated values like `txt,doc,pdf`
- **All extensions**: Press Enter to monitor all file types
- **Directories only**: Don't select any extensions to monitor only directory changes

### Output Format

While running, the application prints output to the console in the following format:

```
[CREATED] example.txt [File] [.txt] Size: 1024 bytes Time: 2025-01-15 10:30:45
[MODIFIED] example.txt [File] [.txt] Size: 2048 bytes Time: 2025-01-15 10:31:20
[DELETED] old_file.txt [File] [.txt] Time: 2025-01-15 10:32:10
[RENAMED] old_name.txt -> new_name.txt [File] [.txt] Time: 2025-01-15 10:33:05
```

### Email Notifications

Email notifications include the following information:

- **File Name**: Name of the file that changed
- **Full Path**: Complete directory path of the file
- **Timestamp**: Time when the change occurred
- **Size**: File size in bytes
- **Type**: Whether it's a file or directory

## Troubleshooting

### config.ini File Not Found

**Issue**: `[ConfigLoader] Warning: Configuration file not found`

**Solution**:
- Make sure `config.ini` is in the same directory as the executable
- Or ensure it's in the project root directory
- Verify the file name is exactly `config.ini` (case-insensitive)

### Email Cannot Be Sent

**Issue**: You see `[EMAIL_ERROR]` messages

**Solutions**:
1. **If using Gmail**: Make sure you're using an App Password
2. **Password check**: If your password contains special characters, ensure they're written correctly
3. **SMTP URL**: If using a custom provider, verify the SMTP URL is correct
4. **Network connection**: Check your internet connection
5. **Firewall**: Ensure the firewall is not blocking port 587

### libcurl Not Found

**Issue**: `CURL not found` error during CMake build

**Solution**:
1. Make sure vcpkg is installed
2. Install libcurl:
   ```powershell
   cd C:\vcpkg
   .\vcpkg install curl:x64-windows-static
   ```
3. Check the vcpkg path in CMakeLists.txt
4. Clear CMake cache and rebuild

### File Changes Not Detected

**Issue**: File changes are not printed to console

**Solutions**:
1. Verify the monitored directory path is correct
2. Ensure the application has access permissions to the directory
3. Verify the file extension filter is configured correctly
4. Try running the application as administrator

## Security Notes

⚠️ **IMPORTANT**: The `config.ini` file contains sensitive information (passwords)!

- This file is in `.gitignore` and should **NOT be added** to your Git repository
- If the file was previously committed, run these commands:
  ```bash
  git rm --cached config.ini
  git commit -m "Remove config.ini from repository"
  ```
- Never share your passwords
- Change your email passwords regularly
- Use App Password for Gmail (instead of regular password)

## License

This project is licensed under [MIT]. See the `LICENSE` file for details.

## Contributing

Contributions are welcome! Please:

1. Fork the project
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## Contact

For questions or suggestions:
- Open an issue: [GitHub Issues](https://github.com/mercethem/event_listener/issues)
- Email: [mercethem@gmail.com]

---

# Dosya Sistemi Olay Dinleyicisi

Windows dosya sistemi izleme ve e-posta bildirim uygulaması. Belirttiğiniz dizindeki dosya değişikliklerini (oluşturma, silme, yeniden adlandırma, değiştirme) gerçek zamanlı olarak izler ve isteğe bağlı olarak e-posta bildirimleri gönderir.

---

## İçindekiler

- [Özellikler](#özellikler)
- [Sistem Gereksinimleri](#sistem-gereksinimleri)
- [Kurulum](#kurulum)
- [Yapılandırma](#yapılandırma)
- [Kullanım](#kullanım)
- [E-posta Ayarları](#e-posta-ayarları)
- [Sorun Giderme](#sorun-giderme)
- [Güvenlik Notları](#güvenlik-notları)
- [Katkıda Bulunma](#katkıda-bulunma)

## Özellikler

- **Gerçek Zamanlı İzleme**: Windows dosya sistemi API'leri kullanarak dizin değişikliklerini anlık olarak izler
- **Dosya Filtreleme**: Belirli dosya uzantılarını filtreleyerek sadece istediğiniz dosya türlerini izleyebilirsiniz
- **E-posta Bildirimleri**: Dosya değişikliklerinde otomatik e-posta bildirimleri gönderir
- **Çoklu E-posta Sağlayıcı Desteği**: Gmail, Outlook, Hotmail, Yandex, Yahoo, iCloud ve özel SMTP sunucuları
- **Detaylı Bilgi**: Dosya adı, tam yol, boyut, zaman damgası ve tür bilgilerini içerir
- **Yapılandırılabilir**: `config.ini` dosyası ile kolay yapılandırma

## Sistem Gereksinimleri

### Gerekli Yazılımlar

- **İşletim Sistemi**: Windows 10 veya üzeri
- **Derleyici**: MSVC (Visual Studio 2019 veya üzeri) veya uyumlu C++20 derleyicisi
- **CMake**: 3.20 veya üzeri
- **C++ Standardı**: C++20

### Bağımlılıklar

- **libcurl**: E-posta gönderme özelliği için (vcpkg ile kurulabilir)
- **zlib**: libcurl'un compression desteği için (libcurl ile birlikte gelir)
- **Windows SDK**: Windows API'leri için

### vcpkg Kurulumu (Önerilen)

1. vcpkg'yi klonlayın:
   ```powershell
   git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
   cd C:\vcpkg
   .\bootstrap-vcpkg.bat
   ```

2. libcurl'ü kurun:
   ```powershell
   .\vcpkg install curl:x64-windows-static
   ```

3. CMakeLists.txt dosyasındaki vcpkg yolunu kendi yolunuza göre güncelleyin:
   ```cmake
   set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
   ```

## Kurulum

### 1. Projeyi Klonlayın

```bash
git clone https://github.com/kullaniciadi/event_listener.git
cd event_listener
```

### 2. CMake ile Derleyin

**CLion kullanıyorsanız:**
- Projeyi açın ve CLion otomatik olarak CMake'i çalıştıracaktır
- Build butonuna tıklayın veya `Ctrl+F9` tuşlarına basın

**Komut satırından:**
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### 3. Yapılandırma Dosyasını Oluşturun

`config.ini` dosyası `.gitignore` içinde olduğu için projeye dahil edilmemiştir. Kendi `config.ini` dosyanızı oluşturun:

```ini
# Takip edilecek dizin
DIRECTORY=C:\Users\YourName\Desktop\monitored

# E-posta ayarları
PROVIDER=Gmail
CUSTOM_SMTP_URL=

# Kimlik Bilgileri
USERNAME=your_email@gmail.com
PASSWORD=your_app_password
RECIPIENT=recipient@example.com
```

## Yapılandırma

### config.ini Dosyası

`config.ini` dosyası uygulamanın ana yapılandırma dosyasıdır. Bu dosya proje kök dizininde, executable'ın bulunduğu dizinde veya çalışma dizininde olabilir.

#### Dosya Konumu Önceliği

Uygulama `config.ini` dosyasını şu sırayla arar:
1. Executable'ın bulunduğu dizin
2. Executable'ın bir üst dizini (proje root)
3. Mevcut çalışma dizini

Eğer dosya bulunamazsa, uygulama interaktif moda geçer ve ayarları kullanıcıdan ister.

#### Yapılandırma Parametreleri

##### DIRECTORY
- **Açıklama**: İzlenmesi gereken dizin yolu
- **Format**: Windows dizin yolu (örn: `C:\Users\YourName\Desktop\monitored`)
- **Zorunlu**: Hayır (boş bırakılırsa kullanıcıdan istenir)
- **Örnek**: `DIRECTORY=C:\Users\merce\Desktop\un`

##### PROVIDER
- **Açıklama**: E-posta sağlayıcısı
- **Değerler**: 
  - `Gmail` - Gmail
  - `Outlook` - Outlook (@outlook.com)
  - `Hotmail` - Hotmail (@hotmail.com, @live.com)
  - `Yandex` - Yandex Mail
  - `Yahoo` - Yahoo Mail
  - `iCloud` - Apple Mail (@me.com, @icloud.com)
  - `Custom` - Özel SMTP sunucusu
- **Zorunlu**: Hayır (boş bırakılırsa e-posta özelliği devre dışı kalır)
- **Örnek**: `PROVIDER=Gmail`

##### CUSTOM_SMTP_URL
- **Açıklama**: Özel SMTP sunucu URL'i (sadece `PROVIDER=Custom` ise gereklidir)
- **Format**: `smtp://sunucu.com:port` (örn: `smtp://smtp.example.com:587`)
- **Zorunlu**: Sadece `PROVIDER=Custom` ise
- **Örnek**: `CUSTOM_SMTP_URL=smtp://smtp.example.com:587`

##### USERNAME
- **Açıklama**: E-posta adresiniz (SMTP kimlik doğrulama için)
- **Format**: E-posta adresi
- **Zorunlu**: E-posta özelliği kullanılacaksa evet
- **Örnek**: `USERNAME=your_email@gmail.com`

##### PASSWORD
- **Açıklama**: E-posta şifreniz veya uygulama şifresi (App Password)
- **Not**: Gmail için normal şifre yerine [App Password](https://support.google.com/accounts/answer/185833) kullanmanız gerekir
- **Zorunlu**: E-posta özelliği kullanılacaksa evet
- **Örnek**: `PASSWORD=abcd efgh ijkl mnop`

##### RECIPIENT
- **Açıklama**: Bildirimlerin gönderileceği e-posta adresi
- **Format**: E-posta adresi
- **Zorunlu**: E-posta özelliği kullanılacaksa evet
- **Örnek**: `RECIPIENT=recipient@example.com`

#### Yorum Satırları

`config.ini` dosyasında `#` ile başlayan satırlar yorum olarak kabul edilir ve işlenmez:

```ini
# Bu bir yorum satırıdır
DIRECTORY=C:\Users\YourName\Desktop\monitored  # Bu da yorum
```

#### Boş Değerler

Bir parametre boş bırakılırsa (örn: `DIRECTORY=`), uygulama bu değeri geçersiz kabul eder ve kullanıcıdan interaktif olarak ister.

## E-posta Ayarları

### Gmail Kullanımı

Gmail için normal şifre yerine **App Password** kullanmanız gerekir:

1. Google Hesabınızda 2 Adımlı Doğrulamayı etkinleştirin
2. [App Passwords](https://myaccount.google.com/apppasswords) sayfasına gidin
3. "Uygulama" için "Mail" seçin
4. "Cihaz" için "Windows Bilgisayar" seçin
5. "Oluştur" butonuna tıklayın
6. Verilen 16 karakterlik şifreyi `config.ini` dosyasındaki `PASSWORD` alanına girin

**Örnek config.ini:**
```ini
PROVIDER=Gmail
USERNAME=your_email@gmail.com
PASSWORD=abcd efgh ijkl mnop
RECIPIENT=recipient@gmail.com
```

### Outlook/Hotmail Kullanımı

Outlook ve Hotmail için normal şifrenizi kullanabilirsiniz:

```ini
PROVIDER=Outlook
USERNAME=your_email@outlook.com
PASSWORD=your_password
RECIPIENT=recipient@outlook.com
```

### Özel SMTP Sunucusu

Kendi SMTP sunucunuzu kullanmak için:

```ini
PROVIDER=Custom
CUSTOM_SMTP_URL=smtp://smtp.example.com:587
USERNAME=your_email@example.com
PASSWORD=your_password
RECIPIENT=recipient@example.com
```

### E-posta Özelliğini Devre Dışı Bırakma

E-posta bildirimlerini kullanmak istemiyorsanız, `config.ini` dosyasında `PROVIDER`, `USERNAME`, `PASSWORD` veya `RECIPIENT` alanlarını boş bırakın veya hiç eklemeyin. Uygulama başlatıldığında e-posta ayarları istenecek, Enter'a basarak atlayabilirsiniz.

## Kullanım

### Temel Kullanım

1. `config.ini` dosyanızı yapılandırın (yukarıdaki bölüme bakın)
2. Uygulamayı çalıştırın:
   ```powershell
   .\event_listener.exe
   ```
3. Eğer `config.ini` dosyasında `DIRECTORY` belirtilmemişse, izlenecek dizini girin
4. İzlenecek dosya uzantılarını seçin (virgülle ayırarak, örn: `txt,doc,pdf`)
5. Enter'a basarak izlemeyi durdurun

### Dosya Uzantı Filtreleme

Uygulama başlatıldığında, izlenecek dosya uzantılarını seçmeniz istenir:

- **Belirli uzantılar**: `txt,doc,pdf` gibi virgülle ayırarak girin
- **Tüm uzantılar**: Enter'a basarak tüm dosya türlerini izleyin
- **Sadece dizinler**: Hiçbir uzantı seçmeyerek sadece dizin değişikliklerini izleyin

### Çıktı Formatı

Uygulama çalışırken konsola şu formatta çıktılar yazdırır:

```
[CREATED] example.txt [File] [.txt] Size: 1024 bytes Time: 2025-01-15 10:30:45
[MODIFIED] example.txt [File] [.txt] Size: 2048 bytes Time: 2025-01-15 10:31:20
[DELETED] old_file.txt [File] [.txt] Time: 2025-01-15 10:32:10
[RENAMED] old_name.txt -> new_name.txt [File] [.txt] Time: 2025-01-15 10:33:05
```

### E-posta Bildirimleri

E-posta bildirimleri şu bilgileri içerir:

- **Dosya Adı**: Değişikliğe uğrayan dosyanın adı
- **Tam Yol**: Dosyanın tam dizin yolu
- **Zaman Damgası**: Değişikliğin gerçekleştiği zaman
- **Boyut**: Dosya boyutu (byte cinsinden)
- **Tür**: Dosya mı yoksa dizin mi olduğu

## Sorun Giderme

### config.ini Dosyası Bulunamıyor

**Sorun**: `[ConfigLoader] Warning: Configuration file not found`

**Çözüm**:
- `config.ini` dosyasının executable ile aynı dizinde olduğundan emin olun
- Veya proje kök dizininde olduğundan emin olun
- Dosya adının tam olarak `config.ini` olduğundan emin olun (büyük/küçük harf duyarlı değil)

### E-posta Gönderilemiyor

**Sorun**: `[EMAIL_ERROR]` mesajları görüyorsunuz

**Çözümler**:
1. **Gmail kullanıyorsanız**: App Password kullandığınızdan emin olun
2. **Şifre kontrolü**: Şifrenizde özel karakterler varsa doğru şekilde yazıldığından emin olun
3. **SMTP URL**: Custom provider kullanıyorsanız SMTP URL'inin doğru olduğundan emin olun
4. **Ağ bağlantısı**: İnternet bağlantınızı kontrol edin
5. **Güvenlik duvarı**: Güvenlik duvarının 587 portunu engellemediğinden emin olun

### libcurl Bulunamıyor

**Sorun**: CMake build sırasında `CURL bulunamadı` hatası

**Çözüm**:
1. vcpkg'nin kurulu olduğundan emin olun
2. libcurl'ü kurun:
   ```powershell
   cd C:\vcpkg
   .\vcpkg install curl:x64-windows-static
   ```
3. CMakeLists.txt dosyasındaki vcpkg yolunu kontrol edin
4. CMake cache'ini temizleyin ve yeniden build edin

### Dosya Değişiklikleri Algılanmıyor

**Sorun**: Dosya değişiklikleri konsola yazdırılmıyor

**Çözümler**:
1. İzlenen dizinin yolunun doğru olduğundan emin olun
2. Uygulamanın dizine erişim izni olduğundan emin olun
3. Dosya uzantı filtresinin doğru yapılandırıldığından emin olun
4. Uygulamayı yönetici olarak çalıştırmayı deneyin

## Güvenlik Notları

⚠️ **ÖNEMLİ**: `config.ini` dosyası hassas bilgiler (şifreler) içerir!

- Bu dosya `.gitignore` içinde olduğu için Git repository'nize **eklenmemelidir**
- Eğer dosya daha önce commit edildiyse, şu komutları çalıştırın:
  ```bash
  git rm --cached config.ini
  git commit -m "Remove config.ini from repository"
  ```
- Şifrelerinizi asla paylaşmayın
- E-posta şifrelerinizi düzenli olarak değiştirin
- Gmail için App Password kullanın (normal şifre yerine)

## Lisans

Bu proje [MIT] altında lisanslanmıştır. Detaylar için `LICENSE` dosyasına bakın.

## Katkıda Bulunma

Katkılarınızı memnuniyetle karşılıyoruz! Lütfen:

1. Projeyi fork edin
2. Feature branch oluşturun (`git checkout -b feature/amazing-feature`)
3. Değişikliklerinizi commit edin (`git commit -m 'Add amazing feature'`)
4. Branch'inizi push edin (`git push origin feature/amazing-feature`)
5. Pull Request oluşturun

## İletişim

Sorularınız veya önerileriniz için:
- Issue açın: [GitHub Issues](https://github.com/kullaniciadi/event_listener/issues)
- E-posta: [mercethem@gmail.com]

---
