/*
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <lpapp@kde.org>
 * Copyright (c) 2014 Felix Rohrbach <kde@fxrh.de>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "playertest.h"

#include <audio/player.h>

#include <core/directoryprovider.h>

#include <QtTest/QtTest>

using namespace GluonAudio;

PlayerTest::PlayerTest()
  : m_audioFilePath(GluonCore::DirectoryProvider::instance()->dataDirectory() + "gluon/audio/Front_Left.wav")
  , m_audioFilePath2(GluonCore::DirectoryProvider::instance()->dataDirectory() + "gluon/audio/Front_Right.wav")
  , m_overRangeValue(10)
{
}

PlayerTest::~PlayerTest()
{
}

void PlayerTest::testAppend()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);

  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);
  
  player.append(m_audioFilePath2);
  QCOMPARE(player.files().at(1), m_audioFilePath2);
  
  // test what happens if we add the same file twice
  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(2), m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);
}

void PlayerTest::testInsert()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);

  player.insert(0, m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.insert(m_overRangeValue, m_audioFilePath2);
  QCOMPARE(player.files().at(1), m_audioFilePath2);
}

void PlayerTest::testRemoveLast()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);

  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.removeLast();
  QCOMPARE(player.files().isEmpty(), true);
}

void PlayerTest::testRemoveAt()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);

  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.removeAt(0);
  QCOMPARE(player.files().isEmpty(), true);
}

void PlayerTest::testIsPlaying()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);
  QCOMPARE(player.isPlaying(), false);

  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.play();
  QCOMPARE(player.isPlaying(), true);

  player.stop();
  QCOMPARE(player.isPlaying(), false);
}

void PlayerTest::testVolume()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);

  ALfloat volume = 0.9f;
  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.setVolume(volume);
  QCOMPARE(player.volume(), volume);
}

void PlayerTest::testIsLooping()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);

  QCOMPARE(player.isLooping(), false);

  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.setLoop(true);
  QCOMPARE(player.isLooping(), true);

  player.setLoop(false);
  QCOMPARE(player.isLooping(), false);
  
  player.append(m_audioFilePath);
  player.setLoop(true);
  player.playAt(0);
  QCOMPARE(player.currentIndex(), 0);
  player.playNext();
  QCOMPARE(player.currentIndex(), 1);
  player.playNext();
  QCOMPARE(player.currentIndex(), 0);
}

void PlayerTest::testPlayNext()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);
  QCOMPARE(player.isPlaying(), false);
  QCOMPARE(player.isLooping(), false);

  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.append(m_audioFilePath2);
  QCOMPARE(player.files().at(1), m_audioFilePath2);

  player.playNext();
  QCOMPARE(player.isPlaying(), true);
  QCOMPARE(player.currentIndex(), 1);

  player.stop();
  QCOMPARE(player.isPlaying(), false);

  player.setLoop(true);
  QCOMPARE(player.isLooping(), true);

  player.playNext();
  QCOMPARE(player.isPlaying(), true);
  QCOMPARE(player.currentIndex(), 0);

  player.stop();
  QCOMPARE(player.isPlaying(), false);
}

void PlayerTest::testPlayAt()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);
  QCOMPARE(player.isPlaying(), false);

  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.playAt(0);
  QCOMPARE(player.isPlaying(), true);

  player.stop();
  QCOMPARE(player.isPlaying(), false);

  player.playAt(m_overRangeValue);
  QCOMPARE(player.isPlaying(), true);

  player.stop();
  QCOMPARE(player.isPlaying(), false);
}

void PlayerTest::testPause()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);
  QCOMPARE(player.isPlaying(), false);

  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.play();
  QCOMPARE(player.isPlaying(), true);

  player.pause();
  QCOMPARE(player.isPlaying(), false);

  player.stop();
  QCOMPARE(player.isPlaying(), false);
}

void PlayerTest::testSeek()
{
}

void PlayerTest::testStop()
{
  Player player(this);
  QCOMPARE(player.files().isEmpty(), true);
  QCOMPARE(player.isPlaying(), false);

  player.append(m_audioFilePath);
  QCOMPARE(player.files().at(0), m_audioFilePath);

  player.play();
  QCOMPARE(player.isPlaying(), true);

  player.stop();
  QCOMPARE(player.isPlaying(), false);
  
  player.append(m_audioFilePath2);
  player.playAt(0);
  QCOMPARE(player.currentIndex(), 0);
  player.stop();
  player.play();
  QCOMPARE(player.currentIndex(), 0);
  player.playNext();
  QCOMPARE(player.currentIndex(), 1);
  player.stop();
  player.play();
  QCOMPARE(player.currentIndex(), 1);
}

QTEST_MAIN(PlayerTest)

 
