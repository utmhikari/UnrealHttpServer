#pragma once

#include "Runtime/Online/HTTPServer/Public/IHttpRouter.h"

namespace UnrealHttpServer
{
	class FWebServer
	{
	public:
		/**
		 * Start server
		 */
		static void Start(uint32 Port);

		/**
		 * Stop server
		 */
		static void Stop();

	private:
		/**
		 * Bind routers with handlers
		 */
		static void BindRouters(const TSharedPtr<IHttpRouter>& HttpRouter);
	};

}