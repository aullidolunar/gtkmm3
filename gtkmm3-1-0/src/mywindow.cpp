#include "mywindow.h"
#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>
#include <iostream>
#include <sstream>
#include <gtkmm/cellrenderer.h>
#include <gtkmm/cellrenderertext.h>

MyListStore::MyListStore()
{
	add(m_col_name);
	add(m_col_subject);
	add(m_col_gade);
	add(m_col_code);
}

MyWindow::MyWindow() :
	border_size(10)
{
	set_title(PROGRAM_TITLE);
	
	auto box_parent = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, border_size);
	box_parent->set_border_width(border_size);
	
	auto frame1 = Gtk::make_managed<Gtk::Frame>("Contenido");
	auto frame1_sw = Gtk::make_managed<Gtk::ScrolledWindow>();
	frame1_sw->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_ALWAYS);
	frame1_sw->set_size_request(350, -1);
	frame1_sw->set_border_width(border_size);
	
	m_refTreeModel = Gtk::ListStore::create(m_list_store);
	// https://docs.huihoo.com/gtkmm/programming-with-gtkmm-3/3.4.1/en/sec-treeview.html
	m_tv = Gtk::make_managed<Gtk::TreeView>(m_refTreeModel);
	m_tv->append_column_editable("Nombre", m_list_store.m_col_name);
	m_tv->append_column("Materia", m_list_store.m_col_subject);
// validated column:
	int npos = m_tv->append_column_numeric_editable("Calificación", m_list_store.m_col_gade, "%.1f");
	auto cellrender = dynamic_cast<Gtk::CellRendererText*>(m_tv->get_column_cell_renderer(npos-1));
	cellrender->signal_edited().connect(sigc::mem_fun(*this, &MyWindow::fn_cell_edited));
//
	m_tv->append_column_numeric("Data", m_list_store.m_col_code, "%i");
	
	Gtk::TreeModel::Row row = *(m_refTreeModel->append());
	row[m_list_store.m_col_name] = "Joel";
	row[m_list_store.m_col_subject] = "Ciencias de la Comunicación";
	row[m_list_store.m_col_gade] = 9.9999;
	row[m_list_store.m_col_code] = 10;
	
	row = *(m_refTreeModel->append());
	row[m_list_store.m_col_name] = "Hannia";
	row[m_list_store.m_col_subject] = "Derecho";
	row[m_list_store.m_col_gade] = 8.2;
	row[m_list_store.m_col_code] = 8;
	
	row = *(m_refTreeModel->append());
	row[m_list_store.m_col_name] = "Koko";
	row[m_list_store.m_col_subject] = "Psicología";
	row[m_list_store.m_col_gade] = 4.9;
	row[m_list_store.m_col_code] = 4;
	
	auto button_layout = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, border_size);
	auto button_exit = Gtk::make_managed<Gtk::Button>("_Salir", true);

// signal handlers:
	button_exit->signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::button_exit_clicked));
	
// layout:
	frame1_sw->add(*m_tv);
	frame1->add(*frame1_sw);
	box_parent->pack_start(*frame1, true, true, 0);
	button_layout->pack_start(*button_exit, false, false, 0);
	box_parent->pack_start(*button_layout, false, false, 0);
	add(*box_parent);
	show_all_children();
}

void MyWindow::fn_cell_edited(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
// Convert the inputed text to double number, as needed by our model column:
	Gtk::TreePath path(path_string);
	Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
	Gtk::TreeModel::Row row = *iter;
	
	std::stringstream ss;
	ss << new_text.raw();
	double new_value;
	ss >> new_value;
	
	std::cout << "double typed=" << new_value << "\n";
	double save_value = new_value;
	if (new_value > 10.0)
	{
		save_value = 10.0;
	}
	else if (new_value < 0.0)
	{
		save_value = 0.0;
	}
	
	row[m_list_store.m_col_gade] = save_value;
	
	std::cout << "double stored=" << save_value << "\n";
}

void MyWindow::button_exit_clicked()
{
	close();
}