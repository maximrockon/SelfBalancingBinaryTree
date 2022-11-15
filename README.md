# SelfBalancingBinaryTree
Решение тестового задания для компании Syntacore
## Краткое описание
Мною на языке C++ были реализованы следующие классы:
+ _Node_ - шаблонный узел двоичного девера, содержащий дополнительную информацию о количестве дочерних узлов для текущего узла;
+ _SelfBalancingBinaryTree_ - шаблонное АВЛ-дерево;
+ _BinaryTreeIterator_ - шаблонный итератор двоичного дерева;
+ _RequestHandler_ - обработчик запросов вида (k v), (m i) и (n j);
+ _StatisticOutOfRange_ - исключение, возникающее при неверно заданном параметре i в запросе вида (m i);
+ _NullPointerDereference_ - исключение, возникающее при попытке разыменования пустого итератора.
## Описание процесса сборки и тестирования
Сборка проекта осуществляется с помощью _cmake_, соответствующий файл _CMakeLists.txt_ прилагается.
Для тестирования можно использовать два консольных приложения:
+ _test.o_ - реализует базовые тесты, написанные мною с использования _GoogleTest_;
+ _tree.o_ - реализует обработку вводимых данных из файла или стандартного ввода (для чтения из файла передайте его полный путь в качестве аргумента командной строки)
