namespace EraDlg
{
	// Bitmask
	enum TSelectDlgFlags : int 
	{
	  SELECT_DLG_NO_FLAG               = 0,  // No flags specified
	  SELECT_DLG_CANCEL_BTN            = 1,  // Add 'cancel' button to dialog
	  SELECT_DLG_LEFT_BTN              = 2,  // Add 'left' button to dialog (used to implement page navigation)
	  SELECT_DLG_RIGHT_BTN             = 4,  // Add 'right' button to dialog (used to implement page navigation)
	  SELECT_DLG_UP_BTN                = 8,  // Add 'up' button to dialog (used by dialog users to show upper level options/help)
	  SELECT_DLG_PAGE_NAV              = 16, // Add 'n/m' page navigation label like 2/6 (second page of 6 max)
	  SELECT_DLG_ALLOW_PAGE_NAV_CLICKS = 32, // Makes page navigation label clickable (which results in SELECT_DLG_RESULT_PAGE_NAV result)
	  SELECT_DLG_REQUIRE_ITEM          = 64; // If set, disallows "OK" button clicks until at least single item becomes selected
	}

	// Bitmask.
	// If SELECT_DLG_ITEM_FROZEN or SELECT_DLG_ITEM_INACTIVE is set, item is not clickable and has gray picture and gray text color
	enum TSelectDlgItemState : int  
	{
	  SELECT_DLG_ITEM_NOT_SELECTED = 0, // Default item state
	  SELECT_DLG_ITEM_SELECTED     = 1, // Item is selected
	  SELECT_DLG_ITEM_FROZEN       = 2, // Item state cannot be changed, item is not clickable
	  SELECT_DLG_ITEM_INACTIVE     = 4, // Item state cannot be changed, item is not clickable. This flag is removed automatically on dependecies resolution event.
	}

	// Item dependencies, used if isMultiple = TRUE. Each list MUST be terminated by -1 value, meaning end. 0..N-1 is item index.
	// After any item is checked, the following process is started:
	//   - iterate through all items, for each item
	//    - remove current item SELECT_DLG_ITEM_INACTIVE flag
	//    - iterate through its 'requiredItems' field. If any requirement is not met, remove current item SELECT_DLG_ITEM_SELECTED flag and add SELECT_DLG_ITEM_INACTIVE flag.
	//    - iterate through its 'forbiddenItems' field. If any of forbidden items is checked, remove current item SELECT_DLG_ITEM_SELECTED flag and add SELECT_DLG_ITEM_INACTIVE flag.
	struct TSelectDlgItemDeps : int  
	{
	  int* requiredItems;  // List of required items. If any of required item is not selected, current item becomes unchecked
	  int* forbiddenItems; // List of disallowed items. If any disallowed item is selected, current item becomes unchecked
	}


	/**
	 * Comments:
	 * ENTER activates OK button, if possible.
	 * ESC activates CANCEL button.
	 * LEFT ARROW/PAGE UP activates LEFT button.
	 * RIGHT ARROW/PAGE DOWN activates RIGHT button.
	 * HOME key activates SELECT_DLG_RESULT_FIRST_PAGE.
	 * END key activates SELECT_DLG_RESULT_LAST_PAGE.
	 * 1-8 key emulate click on item with corresponding index.
	 */
	enum TSelectDlgResult : int  
	{
	  SELECT_DLG_RESULT_OK         = 0, // "OK" button pressed
	  SELECT_DLG_RESULT_CANCEL_BTN = 1, // "Cancel" button pressed
	  SELECT_DLG_RESULT_LEFT_BTN   = 2, // "Left arrow" button pressed
	  SELECT_DLG_RESULT_RIGHT_BTN  = 3, // "Right arrow" button pressed
	  SELECT_DLG_RESULT_UP_BTN     = 4, // "Up arrow" button pressed
	  SELECT_DLG_RESULT_PAGE_NAV   = 5, // Page navigation label is pressed (like 1/2). May occur only if SELECT_DLG_ALLOW_PAGE_NAV_CLICKS is set
	  SELECT_DLG_RESULT_FIRST_PAGE = 6, // Navigation to the first page was triggered. Enabled if current page is non-zero
	  SELECT_DLG_RESULT_LAST_PAGE  = 7, // Navigation to the last page was triggered. Enabled if current page is not (numPages - 1).
	}

	#pragma pack(push, 1);
	struct TSelectDlgConfig 
	{
	  char               *caption;          // Pointer to readonly null-terminated dialog caption
	  int                isMultiple;        // If TRUE, checkboxes are used, radio buttons otherwise, 4 bytes, 0 or 1
	  int                flags;             // TSelectDlgFlags. Dialog setting flags
	  int                numItems;          // Number of items to display
	  char               **itemCaptions;    // List of item captions. Each is null-terminated string. Empty strings are valid.
	  int                *itemStates;       // List of each item state
	  TSelectDlgItemDeps *itemDeps;         // Dependencies for each item. Used if isMultiple = TRUE
	  int                page;              // Current page number, starting from 0 (displayed starting from 1)
	  int                numPages;          // Total number of pages available
	  int                resultClickFlags;  // Mouse flags, set when any button was pressed. Same as CM:F ERM command.
	};
	#pragma pack(pop);

	int __stdcall showSelectDialog (TSelectDlgConfig* dlgConfig);
}

