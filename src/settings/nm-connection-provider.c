/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details:
 *
 * Copyright (C) 2012 Red Hat, Inc.
 */

#include "nm-connection-provider.h"

GSList *
nm_connection_provider_get_best_connections (NMConnectionProvider *self,
                                             guint max_requested,
                                             const char *ctype1,
                                             const char *ctype2,
                                             NMConnectionFilterFunc func,
                                             gpointer func_data)
{
    g_return_val_if_fail (NM_IS_CONNECTION_PROVIDER (self), NULL);

    if (NM_CONNECTION_PROVIDER_GET_INTERFACE (self)->get_best_connections)
        return NM_CONNECTION_PROVIDER_GET_INTERFACE (self)->get_best_connections (self, max_requested, ctype1, ctype2, func, func_data);
	return NULL;
}

/*****************************************************************************/

static void
nm_connection_provider_init (gpointer g_iface)
{
}

GType
nm_connection_provider_get_type (void)
{
	static GType cp_type = 0;

	if (!G_UNLIKELY (cp_type)) {
		const GTypeInfo cp_info = {
			sizeof (NMConnectionProvider), /* class_size */
			nm_connection_provider_init,   /* base_init */
			NULL,       /* base_finalize */
			NULL,
			NULL,       /* class_finalize */
			NULL,       /* class_data */
			0,
			0,          /* n_preallocs */
			NULL
		};

		cp_type = g_type_register_static (G_TYPE_INTERFACE, "NMConnectionProvider", &cp_info, 0);
		g_type_interface_add_prerequisite (cp_type, G_TYPE_OBJECT);
	}

	return cp_type;
}
