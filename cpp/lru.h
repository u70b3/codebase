#pragma once

#include <list>
#include <unordered_map>
#include <cassert>
#include <mutex>

using std::list;
using std::mutex;
using std::pair;
using std::unordered_map;

template <class KeyType, class ValueType>
class LRUCache

{
private:
    list<pair<KeyType, ValueType>> cacheList_;
    unordered_map<KeyType, decltype(cacheList_.begin())> cacheMap_;
    size_t capacity_;
    mutex cache_mutex_;

private:
    void eliminated_(void)
    {
        // 调用情况是有锁环境
        while (cacheMap_.size() > capacity_)
        {
            auto lastIt = cacheList_.end();
            lastIt--;
            cacheMap_.erase(lastIt->first);
            cacheList_.pop_back();
        }
    };

public:
    //单例模式，静态局部变量实现
    static LRUCache<KeyType, ValueType> *getInstance()
    {
        static LRUCache<KeyType, ValueType> lruCache;
        return &lruCache;
    }

public:
    LRUCache(size_t capacity) : capacity_(capacity)
    {
        ;
    };

    // 缓存大小默认 128
    LRUCache() : capacity_(128)
    {
        ;
    };

    void set(const KeyType &key, const ValueType &val)
    {
        std::lock_guard<std::mutex> _(cache_mutex_);
        // 存在的话先删除，统一插入 list 头和更新 hashmap
        if (exist(key))
        {
            auto it = cacheMap_.find(key);
            cacheList_.erase(it->second);
            cacheMap_.erase(it);
        }
        cacheList_.push_front({key, val});
        cacheMap_.insert({key, cacheList_.begin()});
        eliminated_();
    };

    bool exist(const KeyType &key)
    {
        return (cacheMap_.find(key) != cacheMap_.end());
    };

    ValueType get(const KeyType &key)
    {
        std::lock_guard<std::mutex> _(cache_mutex_);
        assert(exist(key));
        cacheList_.splice(cacheList_.begin(), cacheList_, cacheMap_[key]);
        // cacheMap_[key] = cacheList_.begin(); //不需要
        return cacheMap_[key]->second;
    };

    void setCapacity(size_t capacity)
    {
        std::lock_guard<std::mutex> _(cache_mutex_);
        capacity_ = capacity;
    }

    size_t size()
    {
        return cacheMap_.size();
    }
};

