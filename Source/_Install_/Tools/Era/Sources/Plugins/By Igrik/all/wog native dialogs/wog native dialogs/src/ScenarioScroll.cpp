//////////////////////////////////////////////////////////////////////////////////
/////////////// ������ ������ � ������� � ������� ������ �������� ////////////////

int Y_NewScenarioDlg_SetScrolledShoose(_NewScenarioDlg_* dlg, _EventMsg_* msg)
{
    // �������� ������� ��� �������� ����
    _DlgItem_* it = dlg->FindItem(msg->x_abs, msg->y_abs);

    // ���� ������� ����������
    if (it) {
        // �������� id ��������
        int focused_id = it->id;
        
        // ������� id ����������� ��������
        int new_item_id = 0;

        // ����� �� ����� ����������� ������
        _bool_ scroll = false;

        switch (focused_id)
        {
        // �������� ������
        case 370: case 371: case 372: case 373: case 374: case 375: case 376: case 377:
            scroll = true;
            new_item_id = focused_id -147;
            break;

        // �������� ������
        case 362: case 363: case 364: case 365: case 366: case 367: case 368: case 369:
        // �������� ������
        case 378: case 379: case 380: case 381: case 382: case 383: case 384: case 385:
            scroll = true;
            new_item_id = focused_id -123;
            break;

        default:
            break;
        }
        if (scroll) {
            // ���� ������ ����� �� id �������� -8
            if (msg->subtype > 0)
                new_item_id -= 8;

            // ��������� ��� ���������� ������ �� ������ ������� ���
            msg->item_id = new_item_id;
            msg->type = MT_MOUSEBUTTON;
            msg->subtype = MST_LBUTTONCLICK;
            msg->flags = 0;
            return 1;
        }
    }

    return 0;
}
