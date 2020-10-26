#pragma once
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>


using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = int /* тип, используемый для идентификаторов */;

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object);

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
            IdOutputIt ids_begin);

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const;

    // Получить объект по идентификатору
    const T& Get(Id id) const;

    // Увеличить приоритет объекта на 1
    void Promote(Id id);

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const;

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax();

private:
    // Приватные поля и методы
    struct Object {
        T data;
        int priority = 0;
    };
    vector<Object> objects;
    set<pair<int, Id>> sorted_objects;
};



template <typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::Add(T object) {
	Id new_id = objects.size();
	objects.push_back({
        move(object) 
    });
	sorted_objects.insert({
        0, new_id 
    });
	return new_id;
}

template <typename T>
template <typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
	while (range_begin != range_end) {
		*ids_begin = Add(move(*range_begin));
        ids_begin++;
        range_begin++;
	}
}


template <typename T>
bool PriorityCollection<T>::IsValid(Id id) const {
	return id >= 0 && id < static_cast<size_t>(objects.size()) && objects[id].priority != -1;
}

template <typename T>
const T& PriorityCollection<T>::Get(Id id) const {
	return objects[id].data;
}

template <typename T>
void PriorityCollection<T>::Promote(Id id)
{
	auto& item = objects[id];
	sorted_objects.erase({ item.priority, id });
	sorted_objects.insert({ ++item.priority, id });
}

template <typename T>
pair<const T&, int> PriorityCollection<T>::GetMax() const
{
	const auto& item = objects[prev(sorted_objects.end())->second];
	return { item.data, item.priority };
}

template <typename T>
pair<T, int> PriorityCollection<T>::PopMax()
{
	auto sorted_objects_it = prev(sorted_objects.end());
    int in_vector_index = sorted_objects_it->second;
	auto& item = objects[in_vector_index];
	sorted_objects.erase(sorted_objects_it);
    pair<T, int> result = { move(item.data), item.priority };
    item.priority = -1;
	return result;
}