/* BEWARE: new plugin interface, a la GAIM */

#include <glib.h>
#include <gmodule.h>

#include "debug.h"
#include "plugin.h"
#include "common.h"
#include "macros.h"

#ifdef _WIN32
# define PLUGIN_EXT ".dll"
#else
#ifdef __hpux
# define PLUGIN_EXT ".sl"
#else
# define PLUGIN_EXT ".so"
#endif
#endif


/* static GList *loaded_plugins   = NULL; */
/* static GList *plugins          = NULL; */
static GList *load_queue       = NULL;

static size_t search_path_count = 0;
static char **search_paths = NULL;
static int plugins_id_max = 0;


extern gint
gscore_plugins_list(GList *plugins_list)
{
	GList *tmp;

	tmp = g_list_first(plugins_list);

	while (tmp) {
		plugin_pnf *ppnf;

		ppnf = (plugin_pnf *)tmp->data;

		g_print(g_strconcat(ppnf->path, G_DIR_SEPARATOR_S, ppnf->filename, "\n",NULL));
		
		tmp = g_list_next(tmp);
	}

}

extern gint
gscore_plugins_load(GList **plugins_list)
{
	GDir *plugins_dir;
	GError *error = NULL;
	
	plugin_pnf *ppnf;	/* Plugin path and filename infos only (for the linked list) */
	
	const gchar *filename;
	const gchar *full_filename; /* path+filename */
	const gchar *home_dir_plugins_path;

	gboolean is_dir;
	gdouble nb_files = 0;
	
	*plugins_list = NULL;


	/* Register all shared plugins (data_dir) */

	plugins_dir = g_dir_open(get_plugins_path(), 0, &error);
	if ( plugins_dir == NULL ) {
		g_message("Could not open `%s'\n`%s'", get_plugins_path(), error->message);
		g_error_free (error);
		return -1;
	}
	
	while ( (filename = g_dir_read_name(plugins_dir)) != NULL ) {
		full_filename = g_strconcat(get_plugins_path(), G_DIR_SEPARATOR_S, filename, NULL);
		is_dir = g_file_test(full_filename, G_FILE_TEST_IS_DIR);
		
		if (( ! is_dir ) || ( g_ascii_strncasecmp( filename, ".sconsign", 9))) {
			nb_files++;
			
			ppnf = g_malloc(sizeof(plugin_pnf));
			ppnf->path = g_strdup(get_plugins_path()); 
			ppnf->filename = g_strdup(filename);

 			debug_msg(g_strdup_printf("path = %s\nfilename = %s\n", ppnf->path, ppnf->filename));

			*plugins_list = g_list_append(*plugins_list, ppnf);
		}

	}
	
	g_dir_close(plugins_dir);

	
	return nb_files;
}

GscorePlugin *
gscore_plugin_get(const char *filename)
{
	GscorePlugin *plugin;
	GscorePlugin *(*gscore_plugin_init)(void);

	gboolean get_symbol;


	if ( ! g_file_test(filename, G_FILE_TEST_EXISTS) )
		return NULL;

	plugin = (GscorePlugin *)g_malloc(sizeof(*plugin));
	plugin->handle = g_module_open(filename, G_MODULE_BIND_MASK);

	if ( ! plugin->handle ) {
		debug_msg(g_strdup_printf("Error (g_module_open): %s\nCannot open %s\n", g_module_error(), filename));
	}

	get_symbol = g_module_symbol(plugin->handle, "gscore_plugin_init",
				     (gpointer *)(&gscore_plugin_init));

	if ( ! get_symbol ) {

		gw_message_error(g_strdup_printf("Couldn't get the symbol \"gscore_plugin_init\" : %s", g_module_error()));

		g_module_close(plugin->handle);
                plugin->handle = NULL;
                
		return NULL;
	}

	return gscore_plugin_init();
}

GList *
gscore_plugins_get_list_loaded(void)
{
	return load_queue;
}

GscorePlugin *
gscore_plugin_get_from_extension(const gchar *extension)
{
	plugin_pnf *ppnf;
	GscorePlugin *plugin;
	gchar *full_filename;

	gchar *plugin_extension;

	gint i;
	gint j = 0;

	for ( i = 0; i < nb_plugins; i++) {
		ppnf =  g_list_nth_data(plugins_list, i);
		full_filename = g_strconcat(ppnf->path, G_DIR_SEPARATOR_S, ppnf->filename, NULL);

		GSCORE_PLUGIN_INIT(plugin);
		plugin = gscore_plugin_get(full_filename);

		if ( ! plugin) {
			g_printf("Couldn't get the plugin %s!\n", full_filename);
			free(plugin);
			return NULL;
		}

		for ( j = 0; 
		      plugin->filter->extensions[j] != NULL; 
		      j++) {
			plugin_extension = g_strconcat(".", plugin->filter->extensions[j], NULL);

			if (g_ascii_strcasecmp(extension, plugin_extension) == 0)
			{
/* 				g_printf(g_strdup_printf("Extension %s(%s) match plugin %s\n",  */
/* 							  extension, plugin_extension, plugin->info->name)); */
				return plugin;
			}
/* 			return NULL; */
		}
	}

	return NULL;
}

gboolean
gscore_plugin_is_loaded(const GscorePlugin *plugin)
{
	g_return_val_if_fail(plugin != NULL, FALSE);

	return plugin->loaded;
}
