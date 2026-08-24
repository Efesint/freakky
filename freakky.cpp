// g++ freakky.cpp -o freakky $(pkg-config --cflags --libs gtkmm-3.0 vte-2.91)
#include <gtkmm.h>
#include <vte/vte.h>

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.worlds-lightest.terminal", Gio::APPLICATION_NON_UNIQUE);
    
    Gtk::Window window;
    window.set_title("freakky terminal");
    window.set_default_size(900,500);
    
    GtkWidget *vte_widget = vte_terminal_new();
    VteTerminal *vte = VTE_TERMINAL(vte_widget);
    Gtk::Widget *terminal = Glib::wrap(vte_widget);
    

    
    char *shell_argv[2] = {const_cast<char*>("/bin/bash"), nullptr};
    vte_terminal_spawn_async(vte, VTE_PTY_DEFAULT, nullptr,
                              shell_argv, nullptr,
                              G_SPAWN_SEARCH_PATH,
                              nullptr, nullptr, nullptr, -1,
                              nullptr, nullptr, nullptr);
    
    window.add(*terminal);
    window.show_all();
    
    return app->run(window);
}
