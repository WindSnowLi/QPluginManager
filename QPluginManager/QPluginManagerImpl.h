﻿#pragma once

#include <QObject>
#include <QPluginLoader>

#include <optional>

#include "QPluginManager.h"

constexpr auto PLUGIN_SUFFIX = "dll";
constexpr auto NAME = "Name";

class QPluginManagerImpl : public QObject {
private:
    /**
     * @brief {路径，加载器}Map表
     */
    QMap<QString, QPluginLoader*> _pluginMap;
    /**
     * @brief 加载器{路径，对象名}Map表
     */
    QMap<QString, QString> _pathNameMap;
    /**
     * @brief {对象名，指针}Map表
     */
    QMap<QString, QObject*> _objMap;
    /**
     * @brief 加载顺序表
     */
    QList<QString> _paths;

public:
    ~QPluginManagerImpl();

    /**
     * @brief 加载指定路径下的单个插件
     * @param path 精确到dll路径全名称
     */
    void loadPlugin(const QString& path);

    /**
     * @brief 加载指定路径目录下的所有插件
     * @param path 精确到dll路径全名称上级目录
     */
    void loadPlugins(const QString& path);

    /**
     * @brief 递归查找并加载指定目录下的所有插件
     * @param path 递归当前路径
     */
    void findLoadPlugins(const QString& path);

    /**
     * @brief 是否已经加载指定插件名
     * @param name 插件名
     * @return 是否已经加载
     */
    bool isLoad(const QString& name);

    /**
     * @brief 获取加载的插件实例指针
     * @param name 插件实例名
     * @return 插件实例指针
     */
    std::optional<QObject*> load(const QString& name);

    /**
     * @brief 获取插件列表
     * @return 插件名列表
     */
    QList<QString> pluginNames() const;
};
