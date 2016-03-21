#include "LiquidCrystal.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "WProgram.h"


LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
  uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) :
  _four_bit_mode(0), _rs_pin(rs), _rw_pin(rw), _enable_pin(enable)
{
  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3; 
  _data_pins[4] = d4;
  _data_pins[5] = d5;
  _data_pins[6] = d6;
  _data_pins[7] = d7; 
  
  pinMode(_rs_pin, OUTPUT);
  pinMode(_rw_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);
  
  for (int i = 0; i < 8; i++)
    pinMode(_data_pins[i], OUTPUT);
 
  command(0x3A);  // function set: 8 bits, 1 line, 5x8 dots
  command(0x0C);  // display control: turn display on, cursor off, no blinking
  command(0x06);  // entry mode set: increment automatically, display shift, right shift
  clear();
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
  uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) :
  _four_bit_mode(1), _rs_pin(rs), _rw_pin(rw), _enable_pin(enable)
{
  _data_pins[0] = d0;
  _data_pins[1] = d1;
  _data_pins[2] = d2;
  _data_pins[3] = d3; 
  
  pinMode(_rs_pin, OUTPUT);
  pinMode(_rw_pin, OUTPUT);
  pinMode(_enable_pin, OUTPUT);
  
  for (int i = 0; i < 4; i++)
    pinMode(_data_pins[i], OUTPUT);
 
  command(0x2A);  // �� ���ο� 4bit¥�� ���ڿ��� 5*8¥�� dot���� ǥ�� 
  command(0x0C);  // �����̴� ȭ���� �ƴ� ����ؼ� ���̵����ִ»��·� display�� ��Ÿ����
  command(0x06);  //  entry mode set:�ڵ������� push�ؼ� ������ �Է� ���Ŀ� ���������� ��ĭ �̵���Ŵ
  clear();
}

  //clear�Լ�
void LiquidCrystal::clear()
{
  command(0x01); // ȭ�鿡 ������ ���ڸ� ��� ������/
  delayMicroseconds(2000);
}

//Ŀ���� ��ġ�� �������� ���� ó������ �������ְ�����
void LiquidCrystal::home()
{
  command(0x02);  
  delayMicroseconds(2000);
}

void LiquidCrystal::setCursor(int col, int row)
{
  int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
  command(0x80 | (col + row_offsets[row]));
}

void LiquidCrystal::command(uint8_t value) {
  send(value, LOW);
}

void LiquidCrystal::write(uint8_t value) {
  send(value, HIGH);
}

void LiquidCrystal::send(uint8_t value, uint8_t mode) {
  digitalWrite(_rs_pin, mode);
  digitalWrite(_rw_pin, LOW);

  if (_four_bit_mode) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(_data_pins[i], (value >> (i + 4)) & 0x01);
    }
    
    digitalWrite(_enable_pin, HIGH);
    digitalWrite(_enable_pin, LOW);
    
    for (int i = 0; i < 4; i++) {
      digitalWrite(_data_pins[i], (value >> i) & 0x01);
    }

    digitalWrite(_enable_pin, HIGH);
    digitalWrite(_enable_pin, LOW);
  } else {
    for (int i = 0; i < 8; i++) {
      digitalWrite(_data_pins[i], (value >> i) & 0x01);
    }

    digitalWrite(_enable_pin, HIGH);
    digitalWrite(_enable_pin, LOW);
  }
}
