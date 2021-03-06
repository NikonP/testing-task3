/*
 * This file is part of radiooooo-qt
 * GitHub: https://github.com/NikonP/radiooooo-qt
 * configurator.cpp - some functions for storing app configuration in json file
 */

#include "configurator.h"

Configurator::Configurator(QObject *parent) : QObject(parent)
{

}

/*
 * Converts ConfigStorage var to QJsonDocument
 * @return QJsonDocument
 */
QJsonDocument Configurator::configToJson(Configurator::ConfigStorage c) {
    QJsonObject jsonObj;

    for(QString key : c.keys()) {
        QJsonArray jsonArr;
        for(QString val : c[key]) {
            jsonArr.push_back(val);
        }
        jsonObj.insert(key, jsonArr);
    }

    QJsonDocument jsonDoc(jsonObj);
    return jsonDoc;
}

/*
 * Creates app's dirs
 */
void Configurator::initDirs() {
    QDir().mkdir(appDirPath);
    QDir().mkdir(audioDirPath);
}

/*
 * Inits config with default values
 */
void Configurator::initConfig() {
    // remove all
    config.clear();

    // init config with dafault values
    for(QString key : defaultConfig.keys()) {
        config[key].push_back(defaultConfig[key]);
    }

    // save default config
    saveConfig();
}

/*
 * Saves config to json file
 */
void Configurator::saveConfig() {
    QJsonDocument jsonDoc = configToJson(config); // convert config to json

    QFile configFile(configFilePath); // open config file
    if (configFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        configFile.write(jsonDoc.toJson()); // write json data
        configFile.close();
    }
}

/*
 * Loads config from json file
 */
void Configurator::loadConfig() {
    Configurator::ConfigStorage loadedConfig; // result

    QFile configFile(configFilePath); // open config file
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        initConfig(); // init config with default values
        return;
    }

    // json text data to QJsonObject
    QJsonObject jsonObj = QJsonDocument::fromJson(configFile.readAll()).object();

    // QJsonObject to ConfigStorage
    for(QString key : jsonObj.keys()) {
        for(QJsonValueRef val : jsonObj[key].toArray()) {
            loadedConfig[key].push_back(val.toString());
        }
    }

    config = loadedConfig; // save loaded config
}

/*
 * updates param in config
 *
 * @param QString param - key in ConfigStorage var
 * @param QString value - value to add/remove
 * @param bool enable - add or remove
 * adds value if enable==true, removes otherwise
 */
void Configurator::updateConfig(QString param, QString value, bool enable) {
    if(config[param].contains(value) && !enable) {
        config[param].removeAll(value);
    } else if(!config[param].contains(value) && enable) {
        config[param].push_back(value);
    }

    saveConfig();
}

/*
 * Config getter
 * @return ConfigStorage - Configurator class private var
 */
Configurator::ConfigStorage Configurator::getConfig() {
    return config;
}

/*
 * Config getter but it returns string
 * @return QString - Configurator class private var but as string
 */
QString Configurator::getConfigStr() {
    QJsonDocument jsonDoc = configToJson(config);
    QString jsonString = jsonDoc.toJson();
    return jsonString;
}

/*
 * Returns countries for quick setup
 * (for qml)
 * @return json as QString - <ISO-3166-1 Alpha-3>: <name of the country>
 */
QString Configurator::getQuickCountries() {
    QJsonObject jsonObj;
    for(QString key : quickCountries.keys()) {
        jsonObj.insert(key, quickCountries[key]);
    }
    QJsonDocument jsonDoc(jsonObj);
    QString jsonString = jsonDoc.toJson();
    return jsonString;
}
