#ifndef CONFIGURATOR_TESTS_H
#define CONFIGURATOR_TESTS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QDir>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "configurator.h"

using namespace testing;

TEST(init_dirs, check_dirs)
{
    Configurator cfg;
    cfg.initDirs();
    EXPECT_EQ(true, QDir(cfg.appDirPath).exists());
    EXPECT_EQ(true, QDir(cfg.audioDirPath).exists());
}

TEST(init_config, check_data) {
    Configurator cfg;
    cfg.initDirs();
    cfg.initConfig(); // init default
    Configurator::ConfigStorage config = cfg.getConfig();
    for(auto key : cfg.defaultConfig.keys()) {
        EXPECT_EQ(1, config.keys().contains(key));
        EXPECT_EQ(1, config[key].length());
        EXPECT_EQ(1, config[key].contains(cfg.defaultConfig[key]));
    }
}

TEST(save_config, check_file) {
    Configurator cfg;
    cfg.initDirs();
    cfg.initConfig(); // load default
    cfg.saveConfig(); // save deafult

    QFileInfo test_file(cfg.configFilePath);
    EXPECT_EQ(1, test_file.exists());
    EXPECT_EQ(1, test_file.isFile());
}

TEST(load_config, check_data) {
    Configurator cfg;
    cfg.initDirs();
    cfg.initConfig(); // init default
    cfg.saveConfig(); // save deafult
    cfg.loadConfig(); // load from file

    Configurator::ConfigStorage config = cfg.getConfig();
    EXPECT_EQ(1, config.keys().length() != 0);
    for(auto key : cfg.defaultConfig.keys()) {
        EXPECT_EQ(1, config.keys().contains(key));
        EXPECT_EQ(1, config[key].length());
        EXPECT_EQ(1, config[key].contains(cfg.defaultConfig[key]));
    }
}

TEST(update_config, add_val) {
    Configurator cfg;
    cfg.initDirs();
    cfg.initConfig(); // load default

    cfg.updateConfig("moods", "TEST_VAL_1", true);
    cfg.updateConfig("isocodes", "TEST_VAL_2", true);
    cfg.updateConfig("decades", "TEST_VAL_3", true);

    Configurator::ConfigStorage config = cfg.getConfig();

    EXPECT_EQ(1, config["moods"].contains("TEST_VAL_1"));
    EXPECT_EQ(1, config["isocodes"].contains("TEST_VAL_2"));
    EXPECT_EQ(1, config["decades"].contains("TEST_VAL_3"));
}

TEST(update_config, remove_val) {
    Configurator cfg;
    cfg.initDirs();
    cfg.initConfig(); // load default

    cfg.updateConfig("moods", "TEST_VAL_1", true);
    cfg.updateConfig("isocodes", "TEST_VAL_2", true);
    cfg.updateConfig("decades", "TEST_VAL_3", true);

    cfg.updateConfig("moods", "TEST_VAL_1", false);
    cfg.updateConfig("isocodes", "TEST_VAL_2", false);
    cfg.updateConfig("decades", "TEST_VAL_3", false);

    Configurator::ConfigStorage config = cfg.getConfig();

    EXPECT_EQ(0, config["moods"].contains("TEST_VAL_1"));
    EXPECT_EQ(0, config["isocodes"].contains("TEST_VAL_2"));
    EXPECT_EQ(0, config["decades"].contains("TEST_VAL_3"));
}

TEST(update_config, remove_val_not_exist) {
    Configurator cfg;
    cfg.initDirs();
    cfg.initConfig(); // load default

    cfg.updateConfig("moods", "NON_EXISTENT_VAL", false);

    Configurator::ConfigStorage config = cfg.getConfig();

    EXPECT_EQ(0, config["moods"].contains("NON_EXISTENT_VAL"));
}

TEST(update_config, new_key) {
    Configurator cfg;
    cfg.initDirs();
    cfg.initConfig(); // load default

    cfg.updateConfig("NEW_KEY", "VAL", true);

    Configurator::ConfigStorage config = cfg.getConfig();
    qDebug() << config;

    EXPECT_EQ(1, config.keys().contains("NEW_KEY"));
    EXPECT_EQ(1, config["NEW_KEY"].contains("VAL"));
}

TEST(get_config_str, check_data) {
    Configurator cfg;
    cfg.initDirs();
    cfg.initConfig(); // load default
    Configurator::ConfigStorage config = cfg.getConfig();

    QString str = cfg.getConfigStr();
    QJsonObject jsonobj = QJsonDocument::fromJson(str.toUtf8()).object();

    for(auto key : config.keys()) {
        for(auto val : config[key]) {
            EXPECT_EQ(1, jsonobj[key].toArray().contains(val));
        }
    }
}

TEST(get_quick_countries, check_data) {
    Configurator cfg;

    QString str = cfg.getQuickCountries();
    QJsonObject jsonobj = QJsonDocument::fromJson(str.toUtf8()).object();

    for(auto key : cfg.quickCountries.keys()) {
        QString val = cfg.quickCountries[key];
        EXPECT_EQ(1, jsonobj[key].toString() == val);
    }
}

#endif // CONFIGURATOR_TESTS_H
