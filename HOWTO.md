# 🧭 Как сдать домашнее задание через GitHub
Инструкция по работе с репозиторием и сдаче ДЗ.

---

## 1️⃣ Подготовка

Установи утилиты `git` и `make`:

```bash
sudo apt install git make
````

Проверь установку:

```bash
git --version
make --version
```

Убедись, что у тебя есть **аккаунт на GitHub**.

---

## 2️⃣ Форк репозитория

1. Перейди по ссылке на репозиторий преподавателя.
2. Нажми **Fork** в правом верхнем углу.
3. После этого у тебя появится копия (форк) репозитория, например:
   `https://github.com/ТВОЙ_ЛОГИН/cpp-homeworks`

---

## 3️⃣ Настройка GitHub Token (если не SSH)

GitHub больше не принимает обычные пароли для `git push`.
Нужно создать **Personal Access Token (PAT)**:

1. GitHub → **Settings → Developer settings → Personal access tokens → Tokens (classic)**
2. Нажми **Generate new token**
3. Включи галочку **repo**
4. Нажми **Generate token**
5. Скопируй токен и сохрани (он нужен при пуше изменений)

---

## 4️⃣ Клонирование своего форка

```bash
cd ~/projects
git clone https://github.com/ТВОЙ_ЛОГИН/cpp-homeworks.git
cd cpp-homeworks
```

*(Место может быть любым — главное, чтобы ты знал, где проект лежит.)*

---

## 5️⃣ Создание ветки для задания

```bash
git checkout -b task1
```

Теперь ты работаешь в ветке `task1`.

---

## 6️⃣ Выполнение задания

1. Перейди в нужную папку, например:

   ```bash
   cd task1
   ```
2. Отредактируй файл `main.c`
3. Проверь выполнение тестов:

   ```bash
   make build
   make check
   ```

   Добейся вывода:

   ```
   [PASS] Basic pipe
   [PASS] File input
   [PASS] Empty pipe
   ```

---

## 7️⃣ Сохранение изменений

```bash
git add task1/main.c
git commit -m "Homework 1 solution"
git push -u origin task1
```

При первом пуше Git спросит логин и пароль:

* **Username:** твой логин GitHub
* **Password:** вставь **токен**

Чтобы Git запомнил токен:

```bash
git config --global credential.helper store
```

---

## 8️⃣ Создание Pull Request (PR)

1. Перейди в свой репозиторий на GitHub.
2. Нажми **Compare & pull request**
3. Убедись, что:

   * base: `main`
   * compare: `task1`
4. Создай Pull Request.
5. Скопируй ссылку на PR и отправь преподавателю (например, в Telegram).

---

## 9️⃣ После проверки

Когда преподаватель одобрит задание, нажми **Merge pull request**, чтобы влить изменения из `task1` в `main`.

---

## 🔁 Для следующего задания

Перед началом нового задания нужно обновить свой форк и создать новую ветку (например, `task2`).

---

**Шпаргалка:**

> Fork → Clone → Branch → Code → Commit → Push → PR → Merge ✅
