#include "ttscrn.h"

volatile bool UpButtonPressed = false;
volatile bool DownButtonPressed = false;
objects_t objects;
TableRowParameters TabRowPar[TABLE_ROW_NUMBERS];
TbleOverwriteProtect Tabowprct;

ezButton UpButton(UP_BUTTON_PIN);
ezButton DownButton(DOWN_BUTTON_PIN); 

//BUTTON SCROLLING FUNCTIONS USING POLLING, INTERRUPTS AND THE EZBUTTON LIBRARY
void ButtonScroll_Poll(objects_t *ui)
{
 static bool LastUpButtonState = LOW;
 static bool LastDownButtonState = LOW;

 static unsigned long LastUpPressTime = 0;
 static unsigned long LastDownPressTime = 0;

static bool UpHolding = false;
static bool DownHolding = false;

 unsigned long CurrentTime = millis();

 uint8_t  UpButtonState = digitalRead(UP_BUTTON_PIN);
 uint8_t  DownButtonState = digitalRead(DOWN_BUTTON_PIN);
  
  if(UpButtonState) /*First press*/
  {
    if(LastUpButtonState == LOW)
      {
        //lv_obj_scroll_by(ui->order_table,0, SCROLL_AMOUNT, LV_ANIM_ON); //Scrolls the whole object(table). Requires screen refreshment hence slow
        DownScroll(&Tabowprct); //Scrolls by changing row content from one row to another. Seemless and fast
        LastUpPressTime = CurrentTime;
        UpHolding = true;
      }  

     if(UpHolding && ((CurrentTime - LastUpPressTime) > HOLD_TIME))//Auto scrolling after long press
     {
        if(((CurrentTime - LastUpPressTime) >= REPEAT_RATE))
         {
            LastUpPressTime = CurrentTime;
            //lv_obj_scroll_by(ui->order_table,0, SCROLL_AMOUNT, LV_ANIM_ON);
            DownScroll(&Tabowprct);
         }
     }
  }
  else
  {
    UpHolding = false;
  }

  if(DownButtonState)
  {
     if(LastDownButtonState == LOW ) // Up Button pressed
     {
        //lv_obj_scroll_by(ui->order_table,0, -SCROLL_AMOUNT, LV_ANIM_ON);
        UpScroll(&Tabowprct);
        LastDownPressTime = CurrentTime;
        DownHolding = true;
     }
     if(DownHolding && ((CurrentTime - LastDownPressTime) > HOLD_TIME))
     {
         if(((CurrentTime - LastDownPressTime) >= REPEAT_RATE))
         {
            LastDownPressTime = CurrentTime;
            //lv_obj_scroll_by(ui->order_table,0, -SCROLL_AMOUNT, LV_ANIM_ON);
            UpScroll(&Tabowprct);
         }
     }
  }
  else
  {
    DownHolding = false;
  }

  LastUpButtonState = UpButtonState;
  LastDownButtonState = DownButtonState;
}

void ButtonScroll_ez(objects_t *ui) //ezbutton lib
{
 static bool LastUpButtonState = LOW;
 static bool LastDownButtonState = LOW;

 static unsigned long LastUpPressTime = 0;
 static unsigned long LastDownPressTime = 0;

static bool UpHolding = false;
static bool DownHolding = false;

 unsigned long CurrentTime = millis();
   
UpButton.loop();
DownButton.loop();

 bool   UpButtonState = UpButton.isReleased();
 bool  DownButtonState = DownButton.isReleased();
 
  if(UpButtonState) /*First press*/
  {
    if(LastUpButtonState == LOW)
      {
        lv_obj_scroll_by(ui->order_table,0, SCROLL_AMOUNT, LV_ANIM_ON);
        LastUpPressTime = CurrentTime;
        UpHolding = true;
      }  

     if(UpHolding && ((CurrentTime - LastUpPressTime) > HOLD_TIME))
     {
        /*Auto scrolling after long press*/
        if(((CurrentTime - LastUpPressTime) >= REPEAT_RATE))
         {
            LastUpPressTime = CurrentTime;
            lv_obj_scroll_by(ui->order_table,0, SCROLL_AMOUNT, LV_ANIM_ON);
         }
     }
  }
  else
  {
    UpHolding = false;
  }

  if(DownButtonState)
  {
     if(LastDownButtonState == LOW ) // Up Button pressed
     {
        lv_obj_scroll_by(ui->order_table,0, -SCROLL_AMOUNT, LV_ANIM_ON);
        LastDownPressTime = CurrentTime;
        DownHolding = true;
     }
     if(DownHolding && ((CurrentTime - LastDownPressTime) > HOLD_TIME))
     {
         if(((CurrentTime - LastDownPressTime) >= REPEAT_RATE))
         {
            LastDownPressTime = CurrentTime;
            lv_obj_scroll_by(ui->order_table,0, -SCROLL_AMOUNT, LV_ANIM_ON);
         }
     }
  }
  else
  {
    DownHolding = false;
  }

  LastUpButtonState = UpButtonState;
  LastDownButtonState = DownButtonState;
}

void UpButtonISR()
{
  UpButtonPressed = true;
}
void DownButtonISR()
{
  DownButtonPressed = true;
}
void ButtonScroll_IT(objects_t *ui) //Interrupt mode
{
 static unsigned long LastUpPressTime = 0;
 static unsigned long LastDownPressTime = 0;

static bool UpHolding = false;
static bool DownHolding = false;

 unsigned long CurrentTime = millis();
 
  if(UpButtonPressed) /*First press*/
  {
    UpButtonPressed = false;
    if(!UpHolding)
      {
        lv_obj_scroll_by(ui->order_table,0, SCROLL_AMOUNT, LV_ANIM_ON);
        LastUpPressTime = CurrentTime;
        UpHolding = true;
      }  

     if(UpHolding && ((CurrentTime - LastUpPressTime) > HOLD_TIME))
     {
        /*Auto scrolling after long press*/
        if(((CurrentTime - LastUpPressTime) >= REPEAT_RATE))
         {
            LastUpPressTime = CurrentTime;
            lv_obj_scroll_by(ui->order_table,0, SCROLL_AMOUNT, LV_ANIM_ON);
         }
     }
  }
  else
  {
    UpHolding = false;
  }

  if(DownButtonPressed)
  {
    DownButtonPressed = false;
     if(!DownHolding ) // Up Button pressed
     {
        lv_obj_scroll_by(ui->order_table,0, -SCROLL_AMOUNT, LV_ANIM_ON);
        LastDownPressTime = CurrentTime;
        DownHolding = true;
     }
     if(DownHolding && ((CurrentTime - LastDownPressTime) > HOLD_TIME))
     {
         if(((CurrentTime - LastDownPressTime) >= REPEAT_RATE))
         {
            LastDownPressTime = CurrentTime;
            lv_obj_scroll_by(ui->order_table,0, -SCROLL_AMOUNT, LV_ANIM_ON);
         }
     }
  }
  else
  {
    DownHolding = false;
  }
}

void TableFeatures(objects_t* ui)
{
   lv_table_set_row_count(ui->order_table, TABLE_ROW_NUMBERS);
    lv_table_set_column_count(ui->order_table, TABLE_COLUMN_NUMBERS);

    for(int c = 0; c <= 2; c++)
    {
      lv_table_set_column_width(ui->order_table, c, 160);
    }
}

void TableParameters(objects_t* ui) //Updates the table's content
{
    for(uint8_t r = 0; r < TABLE_ROW_NUMBERS; r++ )
    {
      lv_table_set_cell_value(ui->order_table, r, 0, TabRowPar[r].TableID);
      lv_table_set_cell_value(ui->order_table, r, 1, TabRowPar[r].OrderType);
      lv_table_set_cell_value(ui->order_table, r, 2, TabRowPar[r].TimeAgo);  
    }
}

void TableParInit()
{
  for (uint8_t r=0; r < TABLE_ROW_NUMBERS; r++)
  {
    snprintf(TabRowPar[r].TableID, sizeof(TabRowPar[r].TableID), "Table %d", (r+1));
    snprintf(TabRowPar[r].OrderType, sizeof(TabRowPar[r].OrderType), "Order Type %d", (r+1));
    snprintf(TabRowPar[r].TimeAgo, sizeof(TabRowPar[r].TimeAgo), "%d min ago", ((r+1)*5));
  }
}

// void update_row(int row, const char* table, const char* customer, const char* time) {
//     if (row < 0 || row >= MAX_ROWS) return;  // Prevent out-of-bounds access

//     strncpy(table_data[row].table_name, table, sizeof(table_data[row].table_name));
//     strncpy(table_data[row].customer_name, customer, sizeof(table_data[row].customer_name));
//     strncpy(table_data[row].time_ago, time, sizeof(table_data[row].time_ago));

//     lv_table_set_cell_value(ui->order_table, row, 0, table_data[row].table_name);
//     lv_table_set_cell_value(ui->order_table, row, 1, table_data[row].customer_name);
//     lv_table_set_cell_value(ui->order_table, row, 2, table_data[row].time_ago);
// }

void RowUpdate(uint8_t row, const char* TableID, const char* OrderType, const char* TimeAgo)//Row number should be between 1 and TABLE_ROW_NUMBERS
{
       if(row<1 || row >=TABLE_ROW_NUMBERS) return;

       strncpy(TabRowPar[(row-1)].TableID, TableID, sizeof(TabRowPar[(row-1)].TableID));
       strncpy(TabRowPar[(row-1)].OrderType, OrderType, sizeof(TabRowPar[(row-1)].OrderType));
       strncpy(TabRowPar[(row-1)].TimeAgo, TimeAgo, sizeof(TabRowPar[(row-1)].TimeAgo));

       lv_table_set_cell_value(objects.order_table, (row-1), 0, TabRowPar[(row-1)].TableID);
       lv_table_set_cell_value(objects.order_table, (row-1), 1, TabRowPar[(row-1)].OrderType);
       lv_table_set_cell_value(objects.order_table, (row-1), 2, TabRowPar[(row-1)].TimeAgo);

       //TableParameters(&objects);
}

/*Implements cyclic up and down scrolling on the order queue*/
void UpScroll(TbleOverwriteProtect* owptrct)
{
  strcpy(owptrct->TableID_owp, TabRowPar[0].TableID);
  strcpy(owptrct->OrderType_owp, TabRowPar[0].OrderType);
  strcpy(owptrct->TimeAgo_owp, TabRowPar[0].TimeAgo);

  for(uint8_t r=0; r< (TABLE_ROW_NUMBERS-1); r++)
  {
    strcpy(TabRowPar[r].TableID, TabRowPar[r+1].TableID);
    strcpy(TabRowPar[r].OrderType, TabRowPar[r+1].OrderType);
    strcpy(TabRowPar[r].TimeAgo, TabRowPar[r+1].TimeAgo);
    
  }
  strcpy(TabRowPar[TABLE_ROW_NUMBERS-1].TableID, owptrct->TableID_owp);
  strcpy(TabRowPar[TABLE_ROW_NUMBERS-1].OrderType, owptrct->OrderType_owp);
  strcpy(TabRowPar[TABLE_ROW_NUMBERS-1].TimeAgo, owptrct->TimeAgo_owp);

  TableParameters(&objects);

}

void DownScroll(TbleOverwriteProtect* owptrct)
{
  strcpy(owptrct->TableID_owp, TabRowPar[(TABLE_ROW_NUMBERS-1)].TableID);
  strcpy(owptrct->OrderType_owp, TabRowPar[(TABLE_ROW_NUMBERS-1)].OrderType);
  strcpy(owptrct->TimeAgo_owp, TabRowPar[(TABLE_ROW_NUMBERS-1)].TimeAgo);

  for (uint8_t r = (TABLE_ROW_NUMBERS-1); r > 0; r--)
  {
    strcpy(TabRowPar[r].TableID, TabRowPar[r-1].TableID);
    strcpy(TabRowPar[r].OrderType, TabRowPar[r-1].OrderType);
    strcpy(TabRowPar[r].TimeAgo, TabRowPar[r-1].TimeAgo);
  }
  strcpy(TabRowPar[0].TableID, owptrct->TableID_owp);
  strcpy(TabRowPar[0].OrderType, owptrct->OrderType_owp);
  strcpy(TabRowPar[0].TimeAgo, owptrct->TimeAgo_owp);

  TableParameters(&objects);
}