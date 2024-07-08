#ifndef _MYWINDOW_H_INC_
#define _MYWINDOW_H_INC_

#include <gtkmm/window.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodelcolumn.h>

class MyListStore : public Gtk::TreeModelColumnRecord
{
public:
	MyListStore();
	Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	Gtk::TreeModelColumn<Glib::ustring> m_col_subject;
	Gtk::TreeModelColumn<double> m_col_gade;
	Gtk::TreeModelColumn<int> m_col_code;
};

class MyWindow : public Gtk::Window
{
private:
	int border_size;
	MyListStore m_list_store;
	Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
	Gtk::TreeView *m_tv;
public:
	MyWindow();
protected:
	void button_exit_clicked();
	void fn_cell_edited(const Glib::ustring&, const Glib::ustring&);
}; 

#endif
