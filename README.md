Робота з структурованими файлами з індексно-довільним доступом (без СУБД).

Мета роботи – навчитися працювати з структ. файлами без використання СУБД на основі
лише мови С/C++.

В якості предметної області слід вибрати ту, яку ви обрали для ER-моделі. Потрібно
обрати два об’єкти з ER-моделі, які сполучені зв’язком з типом відображення 1-∞. На
основі об’єкту, до якого спрямована 1, формується master-file, а на основі іншого – slave-
file. Програма, яка працює з цими файлами, має включати до свого складу інтерфейс
користувача (на основі командного рядка чи віконний), а також наступні функції:

- функція читання заданого запису та заданих підзаписів на основі прямого
індексного доступу; (get-m, get-s)// підзаписи – записи з slave-file.

- функція вилучення заданого запису чи заданого підзапису; при вилученні запису
необхідно вилучати всі його підзаписи; (del-m, del-s)

- функція оновлення значення заданого поля заданого запису чи заданого підзапису;
(update-m, update-s)

- функція внесення запису та/чи підзаписів в файли (insert-m, insert-s).

- функція підрахунку кількості записів, підзаписів загалом, а також кількості
підзаписів для кожного запису (calc-m, calc-s).

- утиліти (ut-m, ut-s) читання та друку всіх полів (включаючи службові) master-file та
slave-file.